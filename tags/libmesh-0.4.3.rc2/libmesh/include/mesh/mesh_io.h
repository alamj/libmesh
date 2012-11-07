// $Id: mesh_io.h,v 1.2 2004-04-07 21:42:31 benkirk Exp $

// The libMesh Finite Element Library.
// Copyright (C) 2002-2004  Benjamin S. Kirk, John W. Peterson
  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
  
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __mesh_io_h__
#define __mesh_io_h__


// C++ inludes
#include <string>
#include <vector>

// Local includes
#include "libmesh_common.h"
#include "equation_systems.h"




/**
 * This class defines an abstract interface for \p Mesh input and output.
 * Specific classes derived from this class actually implement
 * reading and writing various mesh formats.
 *
 * @author Benjamin S. Kirk, 2004
 */

// ------------------------------------------------------------
// MeshIO class definition
template <class MT>
class MeshIO
{

  /**
   * Both of these methods are protected, since the user should never
   * instantiate a MeshIO object directly.
   *
   * Since certian I/O formats are only defined for reading or writing
   * one or both of these constructors may be implemented by the derived
   * classes.
   */
 protected:
  
  /**
   * Constructor.  Takes a writeable reference to a \p MeshBase object.
   * This is the constructor required to read a mesh.
   */
  MeshIO (MT&);

  /**
   * Constructor.  Takes a reference to a constant mesh object.
   * This constructor will only allow us to write the mesh.
   */
  MeshIO (const MT&);

  
 public:

  /**
   * Destructor.
   */
  virtual ~MeshIO ();
  
  /**
   * This method implements reading a mesh from a specified file.
   */
  virtual void read (const std::string&);
  
  /**
   * This method implements writing a mesh to a specified file.
   */
  virtual void write (const std::string&);

  /**
   * This method implements writing a mesh with data to a specified file
   * where the data is taken from the \p EquationSystems object.
   */
  virtual void write_equation_systems (const std::string&,
				       const EquationSystems&);

  /**
   * This method implements writing a mesh with nodal data to a
   * specified file where the nodal data and variable names are provided.
   */
  virtual void write_nodal_data (const std::string&,
				 const std::vector<Number>&,
				 const std::vector<std::string>&);
  
  /**
   * Returns the \p Mesh objevy as a writeable reference.
   */
  MT& mesh ();

  /**
   * Returns the \p Mesh object as a read-only reference.
   */
  const MT& cmesh () const;

  
 protected:

  
  /**
   * Reads input from \p in, skipping all the lines
   * that start with the character \p comment_start.
   */
  void skip_comment_lines (std::istream& in,
			   const char comment_start);

  
 private:
  

  /**
   * A pointer to a non-const mesh object.  This allows us to read or write
   * the mesh.
   */ 
  MT* _rmesh;
  
  /**
   *  A pointer to a constant mesh object.  This allows us to write
   * meshes that may be passed in as constant objects.
   */
  const MT* const _wmesh;
  
};



// ------------------------------------------------------------
// MeshIO inline members
template <class MT>
inline
MeshIO<MT>::MeshIO (MT& mesh) :
  _rmesh (&mesh),
  _wmesh (&mesh)
{
}



template <class MT>
inline
MeshIO<MT>::MeshIO (const MT& mesh) :
  _rmesh (NULL),
  _wmesh (&mesh)
{
}



template <class MT>
inline
MeshIO<MT>::~MeshIO ()
{
}



template <class MT>
inline
const MT& MeshIO<MT>::cmesh () const
{
  assert (_wmesh != NULL);

  return *_wmesh;
}



template <class MT>
inline
MT& MeshIO<MT>::mesh ()
{
  assert (_rmesh != NULL);

  return *_rmesh;
}



template <class MT>
inline
void MeshIO<MT>::read (const std::string& )
{
  std::cerr << "ERROR:  Must implement the MeshIO::read() member in a derived class!"
	    << std::endl;
  error();
}



template <class MT>
inline
void MeshIO<MT>::write (const std::string& )
{
  std::cerr << "ERROR:  Must implement the MeshIO::write() member in a derived class!"
	    << std::endl;
  error();
}



template <class MT>
inline
void MeshIO<MT>::write_nodal_data (const std::string&,
				   const std::vector<Number>&,
				   const std::vector<std::string>&)
{
  std::cerr << "ERROR:  Must implement the MeshIO::write() member in a derived class!"
	    << std::endl;
  error();
}


#endif // #define __mesh_io_h__