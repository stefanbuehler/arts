/* Copyright (C) 2002-2008 Oliver Lemke <olemke@core-dump.info>

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. */


////////////////////////////////////////////////////////////////////////////
//   File description
////////////////////////////////////////////////////////////////////////////
/*!
  \file   xml_io.cc
  \author Oliver Lemke <olemke@core-dump.info>
  \date   2002-05-10

  \brief This file contains basic functions to handle XML data files.

*/

#include "arts.h"
#include "xml_io.h"
#include "xml_io_private.h"
#include "xml_io_basic_types.h"
#include "xml_io_compound_types.h"
#include "xml_io_array_types.h"
#include "xml_io_instantiation.h"
#include "bofstream.h"
#include "bifstream.h"
#include "file.h"

#ifdef ENABLE_ZLIB
#include "gzstream.h"
#endif


////////////////////////////////////////////////////////////////////////////
//   ArtsXMLTag implementation
////////////////////////////////////////////////////////////////////////////

//! Check tag name
/*!
  Checks whether the name of the tag is correct. Throws runtime
  error otherwise.

  \param expected_name Expected tag name
*/
void
ArtsXMLTag::check_name (const String& expected_name)
{
  if (name != expected_name)
    {
      xml_parse_error ("Tag <" + expected_name + "> expected but <"
                       + name + "> found.");
    }

}


//! Adds a String attribute to tag
/*!

  \param aname Attribute name
  \param value Attribute value
*/
void
ArtsXMLTag::add_attribute (const String& aname, const String& value)
{
  XMLAttribute attr;

  attr.name = aname;
  attr.value = value;
  attribs.push_back (attr);
}


//! Adds an Index attribute to tag
/*!

  \param aname Attribute name
  \param value Attribute value
*/
void
ArtsXMLTag::add_attribute (const String& aname, const Index& value)
{
  ostringstream v;

  v << value;
  add_attribute (aname, v.str ());
}


//! Checks whether attribute has the expected value
/*!

  If the attribute has another value or is unknown an exception is
  thrown.

  \param aname Attribute name
  \param value Expected value
*/
void
ArtsXMLTag::check_attribute (const String& aname, const String& value)
{
  String actual_value;

  get_attribute_value (aname, actual_value);

  if (actual_value == "*not found*")
    {
      xml_parse_error ("Required attribute " + aname
                       + " does not exist");
    }
  else if (actual_value != value)
    {
      xml_parse_error ("Attribute " + aname + " has value "
                       + actual_value + " but "
                       + value + " was expected.");
    }
}


//! Returns value of attribute as String
/*!
  Searches for the matching attribute and returns it value. If no
  attribute with the given name exists, return value is set to
  *not found*.

  \param aname Attribute name
  \param value Return value
*/
void
ArtsXMLTag::get_attribute_value (const String& aname, String& value)
{
  value = "*N/A*";

  Array<XMLAttribute>::iterator it = attribs.begin ();
  while (it != attribs.end ())
    {
      if (it->name == aname)
        {
          value = it->value;
          it = attribs.end ();
        }
      else
        {
          it++;
        }
    }
}


//! Returns value of attribute as type Index
/*!
  Searches for the matching attribute and returns it value. If no
  attribute with the given name exists, return value is set to
  *not found*.

  \param aname Attribute name
  \param value Return value
*/
void
ArtsXMLTag::get_attribute_value (const String& aname, Index& value)
{
  String attribute_value;
  istringstream strstr ("");

  get_attribute_value (aname, attribute_value);
  strstr.str (attribute_value);
  strstr >> value;
  if (strstr.fail ())
    {
      xml_parse_error ("Error while parsing value of " + aname
                       + " from <" + name + ">");
    }
}



//! Reads next XML tag
/*!
  Reads the name and attributes of the next XML tag from stream.

  \param is Input stream
*/
void
ArtsXMLTag::read_from_stream (istream& is)
{
  String        token;
  stringbuf     tag;
  istringstream sstr ("");
  XMLAttribute  attr;
  char          ch;

  attribs.clear ();

  while (is.good () && isspace (is.peek ()))
    {
      is.get ();
    }

  is >> ch;

  if (ch != '<')
    {
      is >> token;
      token = ch + token;

      xml_parse_error ("'<' expected but " + token + " found.");
    }

  is.get (tag, '>');

  // Hit EOF while looking for '>'
  if (is.bad () || is.eof ())
    {
      xml_parse_error ("Unexpected end of file while looking for '>'");
    }

  if (is.get () != '>')
    {
      xml_parse_error ("Closing > not found in tag: " + tag.str ());
    }

  sstr.str (tag.str () + '>');
  out3 << "Read: " << sstr.str () << '\n';

  sstr >> name;

  if (name [name.length () - 1] == '>')
    {
      // Because closin > was found, the tag for sure has no
      // attributes, set token to ">" to skip reading of attributes
      name.erase (name.length () - 1, 1);
      token = ">";
    }
  else
    {
      // Tag may have attributes, so read next token
      sstr >> token;
    }
  out3 << "Name: " << name << '\n';

  //extract attributes
  while (token != ">")
  {
    String::size_type pos;

    pos = token.find ("=", 0);
    if (pos == String::npos)
      {
        xml_parse_error ("Syntax error in tag: " + tag.str ());
      }

    attr.name = token.substr (0, pos);
    token.erase (0, pos + 1);

    if (token[0] != '\"')
      {
        xml_parse_error ("Missing \" in tag: " + tag.str ());
      }

    pos = token.find ("\"", 1);
    if (pos == (String::size_type)String::npos)
      {
        xml_parse_error ("Missing \" in tag: " + sstr.str ());
      }

    attr.value = token.substr (1, pos - 1);

    attribs.push_back (attr);

    out3 << "Attr: " << attr.name << '\n';
    out3 << "Value: " << attr.value << '\n';

    if (token[token.length () - 1] == '>')
      {
        token = ">";
      }
    else
      {
        sstr >> token;
      }
  }

  out3 << '\n';

  // Skip comments
  if (name == "comment")
    {
      is.get (tag, '<');

      // Hit EOF while looking for '<'
      if (is.bad () || is.eof ())
        {
          xml_parse_error ("Unexpected end of file while looking for "
                           "comment tag");
        }

      read_from_stream (is);
      check_name ("/comment");
      read_from_stream (is);
    }
}


//! Write XML tag
/*!
  Puts the tag together and writes it to stream.

  \param os Output stream
*/
void
ArtsXMLTag::write_to_stream (ostream& os)
{

  os << "<" << name;

  Array<XMLAttribute>::iterator it = attribs.begin ();

  while (it != attribs.end ())
    {
      os << ' ' << it->name
         << "=\"" << it->value << '\"';
      it++;
    }

  os << ">";
}



////////////////////////////////////////////////////////////////////////////
//   Default file name
////////////////////////////////////////////////////////////////////////////

//! Gives the default filename for the XML formats.
/*!
  The default name is only used if the filename is empty.

  \param filename filename
  \param varname variable name
*/
void
filename_xml (String&  filename,
              const String&  varname )
{
  if ("" == filename)
    {
      extern const String out_basename;
      filename = out_basename + "." + varname + ".xml";
    }
}



//! Gives the default filename, with file index, for the XML formats.
/*!
  The default name is only used if the filename is empty.

  \param[out] filename   filename
  \param[in]  file_index Index appended to the filename
  \param[in]  varname    variable name
*/
void
filename_xml_with_index (
                    String&  filename,
              const Index&   file_index,
              const String&  varname )
{
  Index dummy = file_index;
  dummy += 1;

  if ("" == filename)
    {
      extern const String out_basename;
      ostringstream os;
      os << out_basename << "." << varname << "." << file_index << ".xml";
      filename = os.str();
    }
  else
    {
      ostringstream os;
      os << filename << "." << file_index << ".xml";
      filename = os.str();
    }
}



////////////////////////////////////////////////////////////////////////////
//   Functions to open and read XML files
////////////////////////////////////////////////////////////////////////////

//! Open file for XML output
/*!
  This function opens an XML file for writing.

  \param file Output filestream
  \param name Filename
*/
void
xml_open_output_file (ofstream& file, const String& name)
{
  // Tell the stream that it should throw exceptions.
  // Badbit means that the entire stream is corrupted, failbit means
  // that the last operation has failed, but the stream is still
  // valid. We don't want either to happen!
  // FIXME: This does not yet work in  egcs-2.91.66, try again later.
  file.exceptions(ios::badbit |
                  ios::failbit);

  // c_str explicitly converts to c String.
  try {
    file.open (name.c_str());
  } catch (ios::failure) {
    ostringstream os;
    os << "Cannot open output file: " << name << '\n'
      << "Maybe you don't have write access "
      << "to the directory or the file?";
    throw runtime_error(os.str());
  }


  // See if the file is ok.
  // FIXME: This should not be necessary anymore in the future, when
  // g++ stream exceptions work properly. (In that case we would not
  // get here if there really was a problem, because of the exception
  // thrown by open().)
  if (!file)
    {
      ostringstream os;
      os << "Cannot open output file: " << name << '\n'
         << "Maybe you don't have write access "
         << "to the directory or the file?";
      throw runtime_error(os.str());
    }
}

#ifdef ENABLE_ZLIB

//! Open file for zipped XML output
/*!
  This function opens a zipped XML file for writing.

  \param file Output filestream
  \param name Filename
*/
void
xml_open_output_file (ogzstream& file, const String& name)
{
  // Tell the stream that it should throw exceptions.
  // Badbit means that the entire stream is corrupted, failbit means
  // that the last operation has failed, but the stream is still
  // valid. We don't want either to happen!
  // FIXME: This does not yet work in  egcs-2.91.66, try again later.
  file.exceptions(ios::badbit |
                  ios::failbit);

  // c_str explicitly converts to c String.
  String nname = name;
  
  if (nname.substr (nname.length()-3, 3) != ".gz")
    {
      nname += ".gz";
    }

  try {
    file.open (nname.c_str());
  } catch (ios::failure) {
    ostringstream os;
    os << "Cannot open output file: " << nname << '\n'
      << "Maybe you don't have write access "
      << "to the directory or the file?";
    throw runtime_error(os.str());
  }


  // See if the file is ok.
  // FIXME: This should not be necessary anymore in the future, when
  // g++ stream exceptions work properly. (In that case we would not
  // get here if there really was a problem, because of the exception
  // thrown by open().)
  if (!file)
    {
      ostringstream os;
      os << "Cannot open output file: " << nname << '\n'
         << "Maybe you don't have write access "
         << "to the directory or the file?";
      throw runtime_error(os.str());
    }
}

#endif /* ENABLE_ZLIB */

//! Open file for XML input
/*!
  This function opens an XML file for reading.

  \param ifs   Input filestream
  \param name  Filename
*/
void
xml_open_input_file (ifstream& ifs, const String& name)
{
  // Tell the stream that it should throw exceptions.
  // Badbit means that the entire stream is corrupted.
  // On the other hand, end of file will not lead to an exception, you
  // have to check this manually!
  ifs.exceptions (ios::badbit);

  // c_str explicitly converts to c String.
  try
    {
      ifs.open (name.c_str ());
    }
  catch (ios::failure)
    {
      ostringstream os;
      os << "Cannot open input file: " << name << '\n'
        << "Maybe the file does not exist?";
      throw runtime_error (os.str ());
    }

  // See if the file is ok.
  // FIXME: This should not be necessary anymore in the future, when
  // g++ stream exceptions work properly.
  if (!ifs)
    {
      ostringstream os;
      os << "Cannot open input file: " << name << '\n'
         << "Maybe the file does not exist?";
      throw runtime_error (os.str ());
    }

  out3 << "- Reading input file " << name << "\n";
}


#ifdef ENABLE_ZLIB

//! Open file for zipped XML input
/*!
  This function opens a zipped XML file for reading.

  \param ifs   Input filestream
  \param name  Filename
*/
void
xml_open_input_file (igzstream& ifs, const String& name)
{
  // Tell the stream that it should throw exceptions.
  // Badbit means that the entire stream is corrupted.
  // On the other hand, end of file will not lead to an exception, you
  // have to check this manually!
  ifs.exceptions (ios::badbit);

  // c_str explicitly converts to c String.
  try
    {
      ifs.open (name.c_str ());
    }
  catch (ios::failure)
    {
      ostringstream os;
      os << "Cannot open input file: " << name << '\n'
        << "Maybe the file does not exist?";
      throw runtime_error (os.str ());
    }

  // See if the file is ok.
  // FIXME: This should not be necessary anymore in the future, when
  // g++ stream exceptions work properly.
  if (!ifs)
    {
      ostringstream os;
      os << "Cannot open input file: " << name << '\n'
         << "Maybe the file does not exist?";
      throw runtime_error (os.str ());
    }

  out3 << "- Reading input file " << name << "\n";
}

#endif /* ENABLE_ZLIB */


////////////////////////////////////////////////////////////////////////////
//   General XML functions (file header, start root tag, end root tag)
////////////////////////////////////////////////////////////////////////////

//! Throws XML parser runtime error
/*!
  This is used quite often inside the parsing routines so it's a
  function for itself.

  \param str_error Error description
*/
void
xml_parse_error (const String& str_error)
{
  ostringstream os;
  os << "XML parse error: " << str_error << '\n'
     << "Check syntax of XML file\n";
  throw runtime_error (os.str ());
}


//! Throws XML parser runtime error
/*!
  This is used quite often inside the data parsing routines so it's a
  function for itself.

  \param tag        ArtsXMLTag
  \param str_error  Error description
*/
void
xml_data_parse_error (ArtsXMLTag& tag, String str_error)
{
  ostringstream os;
  os << "XML data parse error: Error reading ";
  tag.write_to_stream (os);
  os << str_error << "\n"
    << "Check syntax of XML file. A possible cause is that the file "
    << "contains NaN or Inf values.\n";
  throw runtime_error (os.str ());
}


//! Reads XML header and root tag
/*!
  Check whether XML file has correct version tag and reads arts root
  tag information.

  \param is     Input stream
  \param ftype  File type
  \param ntype  Numeric type
  \param etype  Endian type
*/
void
xml_read_header_from_stream (istream& is, FileType& ftype, NumericType& ntype,
                             EndianType& etype)
{
  char str[6];
  stringbuf strbuf;
  ArtsXMLTag tag;
  String strtype;

  is.get (str, 6);

  //if (strcasecmp (str, "<?xml"))
  if (string(str) != "<?xml")
    {
      xml_parse_error ("Input file is not a valid xml file "
                       "(<?xml not found)");
    }

  is.get (strbuf, '>');
  is.get ();

  if (is.fail ())
    {
      xml_parse_error ("Input file is not a valid xml file");
    }

  tag.read_from_stream (is);
  tag.check_name ("arts");

  // Check file format
  tag.get_attribute_value ("format", strtype);
  if (strtype == "binary")
    {
      ftype = FILE_TYPE_BINARY;
    }
  else
    {
      ftype = FILE_TYPE_ASCII;
    }

  // Check endian type
  tag.get_attribute_value ("endian_type", strtype);
  if (strtype == "little")
    {
      etype = ENDIAN_TYPE_LITTLE;
    }
  if (strtype == "big")
    {
      etype = ENDIAN_TYPE_BIG;
    }
  if (strtype == "*N/A*")
    {
/*      out1 << "  Warning: Endian type not specified in XML file, "
        <<    "assuming little endian (PC)\n";*/
      etype = ENDIAN_TYPE_LITTLE;
    }
  else
    {
      ostringstream os;
      os << "  Error: Unknown endian type \"" << strtype
        <<  "\" specified in XML file.\n";
        throw runtime_error(os.str());
    }

  // Check numeric type
  tag.get_attribute_value ("numeric_type", strtype);
  if (strtype == "float")
    {
      ntype = NUMERIC_TYPE_FLOAT;
    }
  else if (strtype == "double")
    {
      ntype = NUMERIC_TYPE_DOUBLE;
    }
  else if (strtype == "*N/A*")
    {
/*      out1 << "  Warning: Numeric type not specified in XML file, "
        <<    "assuming double\n";*/
      ntype = NUMERIC_TYPE_DOUBLE;
    }
  else
    {
      ostringstream os;
      os << "  Error: Unknown numeric type \"" << strtype
        <<  "\" specified in XML file.\n";
        throw runtime_error(os.str());
    }

}


//! Reads closing root tag
/*!
  Checks whether XML file ends correctly with \</arts\>.

  \param is  Input stream
*/
void
xml_read_footer_from_stream (istream& is)
{
  ArtsXMLTag tag;

  tag.read_from_stream (is);
  tag.check_name ("/arts");
}


//! Writes XML header and root tag
/*!
  \param os     Output stream
  \param ftype  File type
*/
void
xml_write_header_to_stream (ostream& os, FileType ftype)
{
  ArtsXMLTag tag;

  os << "<?xml version=\"1.0\"?>"
     << '\n';

  tag.set_name ("arts");
  switch (ftype)
    {
  case FILE_TYPE_ASCII:
  case FILE_TYPE_ZIPPED_ASCII:
    tag.add_attribute ("format", "ascii");
    break;
  case FILE_TYPE_BINARY:
    tag.add_attribute ("format", "binary");
    break;
    }

  tag.add_attribute ("version", "1");

  tag.write_to_stream (os);

  os << '\n';

}


//! Write closing root tag
/*!
  \param os Output stream
*/
void
xml_write_footer_to_stream (ostream& os)
{
  ArtsXMLTag tag;

  tag.set_name ("/arts");
  tag.write_to_stream (os);

  os << endl;
}

void
xml_set_stream_precision (ostream& os)
{
  // Determine the precision, depending on whether Numeric is double
  // or float:
  Index precision;
#ifdef USE_FLOAT
  precision = FLT_DIG;
#else
#ifdef USE_DOUBLE
  precision = DBL_DIG;
#else
#error Numeric must be double or float
#endif
#endif

  os << setprecision (precision);
}


////////////////////////////////////////////////////////////////////////////
//   Generic IO routines for XML files
////////////////////////////////////////////////////////////////////////////

//! Reads data from XML file
/*!
  This is a generic functions that is used to read the XML header and
  footer info and calls the overloaded functions to read the data.

  \param filename XML filename
  \param type Generic return value
*/
template<typename T> void
xml_read_from_file (const String& filename,
                    T&            type)
{
  istream* ifs;
  FileType ftype;
  NumericType ntype;
  EndianType etype;

  out2 << "  Reading " << filename << '\n';

  String xml_file = filename;
  bool found_file;

  found_file = find_file (xml_file, ".xml");
  if (!found_file) found_file = find_file (xml_file, ".xml.gz");
  if (!found_file) found_file = find_file (xml_file, ".gz");

  // Open input stream:
  if (xml_file.substr (xml_file.length () - 3, 3) == ".gz")
#ifdef ENABLE_ZLIB
    {
      ifs = new igzstream();
      xml_open_input_file (*(igzstream *)ifs, xml_file);
    }
#else
    {
      throw runtime_error (
        "This arts version was compiled without zlib support.\n"
        "Thus zipped xml files cannot be read.");
    }
#endif /* ENABLE_ZLIB */
  else
    {
      ifs = new ifstream();
      xml_open_input_file (*(ifstream *)ifs, xml_file);
    }

  // No need to check for error, because xml_open_input_file throws a
  // runtime_error with an appropriate error message.

  // Read the matrix from the stream. Here we catch the exception,
  // because then we can issue a nicer error message that includes the
  // filename.
  try
    {
      xml_read_header_from_stream (*ifs, ftype, ntype, etype);
      if (ftype == FILE_TYPE_ASCII)
        {
          xml_read_from_stream (*ifs, type);
        }
      else
        {
          String bfilename = filename + ".bin";
          bifstream bifs (bfilename.c_str ());
          xml_read_from_stream (*ifs, type, &bifs);
        }
      xml_read_footer_from_stream (*ifs);
    }
  catch (runtime_error e)
    {
      delete ifs;
      ostringstream os;
      os << "Error reading file: " << filename << '\n'
         << e.what ();
      throw runtime_error (os.str ());
    }

  delete ifs;
}


void
xml_read_arts_catalogue_from_file (const String&      filename,
                                   ArrayOfLineRecord& type,
                                   const Numeric&     fmin,
                                   const Numeric&     fmax)
{
  istream* ifs;
  FileType ftype;
  NumericType ntype;
  EndianType etype;

  out2 << "  Reading " << filename << '\n';

  String xml_file = filename;
  bool found_file;

  found_file = find_file (xml_file, ".xml");
  if (!found_file) found_file = find_file (xml_file, ".xml.gz");
  if (!found_file) found_file = find_file (xml_file, ".gz");

  // Open input stream:
  if (xml_file.substr (xml_file.length () - 3, 3) == ".gz")
#ifdef ENABLE_ZLIB
    {
      ifs = new igzstream();
      xml_open_input_file (*(igzstream *)ifs, xml_file);
    }
#else
    {
      throw runtime_error (
        "This arts version was compiled without zlib support.\n"
        "Thus zipped xml files cannot be read.");
    }
#endif /* ENABLE_ZLIB */
  else
    {
      ifs = new ifstream();
      xml_open_input_file (*(ifstream *)ifs, xml_file);
    }

  // No need to check for error, because xml_open_input_file throws a
  // runtime_error with an appropriate error message.

  // Read the matrix from the stream. Here we catch the exception,
  // because then we can issue a nicer error message that includes the
  // filename.
  try
    {
      xml_read_header_from_stream (*ifs, ftype, ntype, etype);
      if (ftype == FILE_TYPE_ASCII)
        {
          xml_read_from_stream (*ifs, type, fmin, fmax);
        }
      else
        {
          String bfilename = filename + ".bin";
          bifstream bifs (bfilename.c_str ());
          xml_read_from_stream (*ifs, type, fmin, fmax, &bifs);
        }
      xml_read_footer_from_stream (*ifs);
    }
  catch (runtime_error e)
    {
      delete ifs;
      ostringstream os;
      os << "Error reading file: " << filename << '\n'
         << e.what ();
      throw runtime_error (os.str ());
    }

  delete ifs;
}


//! Write data to XML file
/*!
  This is a generic functions that is used to write the XML header and
  footer info and calls the overloaded functions to write the data.

  \param filename  XML filename
  \param type      Generic input value
  \param ftype     File type
*/
template<typename T> void
xml_write_to_file (const String&  filename,
                   const T&       type,
                         FileType ftype)
{
  ostream* ofs;
 
  out2 << "  Writing " << filename << '\n';
  if (ftype == FILE_TYPE_ZIPPED_ASCII)
#ifdef ENABLE_ZLIB
    {
      ofs = new ogzstream();
      xml_open_output_file(*(ogzstream *)ofs, filename);
    }
#else
    {
      throw runtime_error (
        "This arts version was compiled without zlib support.\n"
        "Thus zipped xml files cannot be written.");
    }
#endif /* ENABLE_ZLIB */
  else
    {
      ofs = new ofstream();
      xml_open_output_file(*(ofstream *)ofs, filename);
    }


  try
    {
      xml_write_header_to_stream (*ofs, ftype);
      if (ftype == FILE_TYPE_ASCII || ftype == FILE_TYPE_ZIPPED_ASCII)
        {
          xml_write_to_stream (*ofs, type);
        }
      else
        {
          String bfilename = filename + ".bin";
          bofstream bofs (bfilename.c_str ());
          xml_write_to_stream (*ofs, type, &bofs);
        }

      xml_write_footer_to_stream (*ofs);
    }
  catch (runtime_error e)
    {
      delete ofs;
      ostringstream os;
      os << "Error writing file: " << filename << '\n'
         << e.what ();
      throw runtime_error (os.str ());
    }

  delete ofs;
}

