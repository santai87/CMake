/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
/**
 * cmCollectFlags - collect flags from CMakeLists.txt files.
 * This class collects include and link flags from a CMakeLists.txt
 * file and any CMakeLists.txt files above it in the directory tree.
 * It stops searching wen the home directory is found.
 */
#ifndef cmCollectFlags_h
#define cmCollectFlags_h

#include <vector>
#include <string>
class cmMakefile;

class cmCollectFlags
{
public:
  cmCollectFlags();
  ~cmCollectFlags ();
  /**
   * Set the home directory for the source code.
   */
  void SetSourceHomeDirectory(const char* dir);
  /**
   * Set the start directory to look for flags 
   */
  void SetStartDirectory(const char* dir);
  /**
   * Parse the directory and all of it's parents for config
   * information
   */
  void ParseDirectories();
  /**
   * Print to standard out
   */
  void Print();
  
  /**
   * Expance varibles for home and binary root in the collected flags.
   * CMAKE_BINARY_DIR and CMAKE_SOURCE_ROOT are replaced with
   * makefile->GetOutputHomeDirectory() and
   * makefile->GetHomeDirectory()
   */
  void ExpandVaribles(cmMakefile* makefile);
  
  std::vector<std::string>& GetIncludeDirectories()
    { 
      return m_IncludeDirectories;
    }
  
  std::vector<std::string>& GetLinkDirectories()
    { 
      return m_LinkDirectories;
    }
  
  std::vector<std::string>& GetLinkLibraries()
    { 
      return m_LinkLibraries;
    }
  
  std::vector<std::string>& GetLinkLibrariesWin32()
    { 
      return m_LinkLibrariesWin32;
    }
  
  std::vector<std::string>& GetLinkLibrariesUnix()
    { 
      return m_LinkLibrariesUnix;
    }
  
private:
  /**
   * Look for CMakeLists.txt files to parse in dir,
   * then in dir's parents, until the SourceHome directory
   * is found.
   */
  void ParseDirectory(const char* dir);
  /**
   * Parse a file for includes links and libs
   */
  void ParseFile(const char* dir);
  
  
  std::string m_SourceHomeDirectory; // source code top level dir
  std::string m_StartDirectory; // source code sub directory
  std::vector<std::string> m_IncludeDirectories;
  std::vector<std::string> m_LinkDirectories;
  std::vector<std::string> m_LinkLibraries;
  std::vector<std::string> m_LinkLibrariesWin32;
  std::vector<std::string> m_LinkLibrariesUnix;
};

#endif
