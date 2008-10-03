/* Copyright (C) 2000-2008 Stefan Buehler <sbuehler@ltu.se>

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

/**
  \file   wsv_aux.h
  \brief  Auxiliary header stuff related to workspace variable
          groups. Normally you should not need to edit this file. 


  \author Stefan Buehler
  \date   2000-06-10
*/

#ifndef wsv_aux_h
#define wsv_aux_h

#include "arts.h"
#include "array.h"
#include "exceptions.h"

// Global functions
void get_wsv_group_ids(ArrayOfIndex& ids, String name);
Index get_wsv_group_id(const String& name);

/** This class contains all static information for one workspace
    variable.

    The program make_wsv_h.cc uses these records to generate the file
    wsv.h, which contains both the declaration of the wsv handles and
    the declaration of the workspace itself.

    \author Stefan Buehler */
class WsvRecord {
public:

  /** Default constructor. */
  WsvRecord() : mname(),
                mdescription(),
                mgroup(-1),
                mimplicit(false)
  { /* Nothing to do here */ }

  /** Initializing constructor.

    This is used by Workspace::define_wsv_data() to set the information for
    each workspace variable. */
  WsvRecord(const char  name[],
            const char  description[],
            const String group,
            const bool  implicit = false)
    : mname(name),
      mdescription(description),
      mgroup(-1),
      mimplicit(implicit)
  {
    // Map the group names to groups' indexes
    mgroup = get_wsv_group_id(group);
    if (mgroup == -1)
      {
        ostringstream os;

        os << "Unknown WSV Group " << group << " WSV " << mname;
        throw runtime_error( os.str() );
      }
  }

  /** Initializing constructor.

    This is used by the parser to create automatically allocated variables */
  WsvRecord(const char  name[],
            const char  description[],
            const Index group,
            const bool  implicit = false)
    : mname(name),
      mdescription(description),
      mgroup(group),
      mimplicit(implicit)
  {
    // Nothing to do here
  }
  /** Name of this workspace variable. */
  const String&  Name()        const { return mname;        }   
  /** A text describing this workspace variable. */
  const String&  Description() const { return mdescription; }
  /** The wsv group to which this variable belongs. */
  Index   Group()       const { return mgroup;       }
  /** Returns true if the variable was automatically created. */
  bool    Implicit()    const { return mimplicit;       }
private:
  String mname;
  String mdescription;
  Index mgroup;
  bool mimplicit;
};

/** Output operator for WsvRecord.
  \author Stefan Buehler */
ostream& operator<<(ostream& os, const WsvRecord& wr);


//! Print list of WSV names to output stream.
/** Runs through the list of WSV indexes and print all names
    to the given output stream. The list of indexes can be any
    STL container such as Array, vector...

    \param outstream OutputStream
    \param container List of WSV indexes
  */
template <typename OutputStream, typename Container> void
PrintWsvNames (OutputStream& outstream, const Container& container)
{
  for (typename Container::const_iterator it = container.begin ();
       it != container.end (); it++ )
    {
      PrintWsvName (outstream, *it);
    }

}

#endif   // wsv_aux_h
