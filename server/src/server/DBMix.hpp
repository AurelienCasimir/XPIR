/* Copyright (C) 2014 Carlos Aguilar Melchor, Joris Barrier, Marc-Olivier Killijian
 * This file is part of XPIR.
 *
 *  XPIR is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  XPIR is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XPIR.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DEF_DBMIX
#define DEF_DBMIX

#include "DBHandler.hpp"
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/thread.hpp>
#include <dirent.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <omp.h>
#include <random>

#define DEFAULT_DIR_NAME "db/"
#define NB_FILE_DESCRIPTORS 50

class DBMix : public DBHandler
{
private:
	boost::mutex mutex;
  std::string directory;
  std::vector<std::ifstream*> fdPool; // a pool of file descriptors
  std::vector <std::string> file_list; // the output file list
  std::vector <std::string> real_file_list; // the list of file that are not generated
  std::string realFileName; // The name of the unique file in case of splitting
  
public:
  DBMix(uint64_t nbStreams);
	virtual ~DBMix();
  
  std::string getCatalog(const bool typeOfCatalog);
  
  uint64_t getDBSizeBits();
  uint64_t getNbStream();
  uint64_t getmaxFileBytesize();
  
  std::ifstream* openStream(uint64_t streamNb, uint64_t requested_offset);
  uint64_t readStream(std::ifstream* s,char * buf, uint64_t size);
  void readAggregatedStream(uint64_t streamNb, uint64_t alpha, uint64_t offset, uint64_t bytes_per_file, char* rawBits);
  void closeStream(std::ifstream* s);
  
  
	std::streampos getFileSize( std::string filePath );
private:
  std::mt19937_64 random_engine; // Fixed seed of 0
  std::uniform_int_distribution<> random_distribution;
 	uint64_t maxFileBytesize; 
};

#endif //DEF_CATALOGMAKER
