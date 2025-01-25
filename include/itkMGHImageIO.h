/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef itkMGHImageIO_h
#define itkMGHImageIO_h

#include "itkMatrix.h"
#include "itkImageIOBase.h"
#include <fstream>
#include "itk_zlib.h"

#include "MGHIOExport.h"

namespace itk
{
/** \class MGHImageIO
 *
 * \author Hans J. Johnson
 * \brief Class that defines how to read MGH file format.
 * Originally developed as part of the Slicer software
 * package under grants XXXX
 *
 * \ingroup IOFilters
 * \ingroup MGHIO
 */
class MGHIO_EXPORT MGHImageIO : public ImageIOBase
{
public:
  /** Standard class type alias. */
  using Self = MGHImageIO;
  using Superclass = ImageIOBase;
  using Pointer = SmartPointer<Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(MGHImageIO);

  /*-------- This part of the interfaces deals with reading data. ----- */

  /** Determine if the file can be read with this ImageIO implementation.
   * \param FileNameToRead The name of the file to test for reading.
   * \post Sets classes ImageIOBase::m_FileName variable to be FileNameToWrite
   * \return Returns true if this ImageIO can read the file specified.
   */
  bool
  CanReadFile(const char * FileNameToRead) override;

  /** Set the spacing and dimension information for the set filename. */
  void
  ReadImageInformation() override;

  /** Reads the data from disk into the memory buffer provided. */
  void
  Read(void * pData) override;

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine if the file can be written with this ImageIO implementation.
   * \param FileNameToWrite The name of the file to test for writing.
   * \post Sets classes ImageIOBase::m_FileName variable to be FileNameToWrite
   * \return Returns true if this ImageIO can write the file specified.
   */
  bool
  CanWriteFile(const char * name) override;

  /** Set the spacing and dimension information for the set filename. */
  void
  WriteImageInformation() override;

  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegions has been set properly. */
  void
  Write(const void * buffer) override;

protected:
  MGHImageIO();
  ~MGHImageIO() override;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  void
  ReadVolumeHeader();

private:
  static const int          MRI_UCHAR = 0;
  static const int          MRI_INT = 1;
  static const int          MRI_FLOAT = 3;
  static const int          MRI_SHORT = 4;
  static const int          MRI_TENSOR = 6;
  static const unsigned int FS_DIMENSION_HEADER_SIZE = sizeof(int) * 7;
  static const unsigned int FS_RAS_HEADER_SIZE = (sizeof(float) * 15) + sizeof(short);
  static const unsigned int FS_UNUSED_HEADER_SIZE = 256 - FS_RAS_HEADER_SIZE;
  static const unsigned int FS_WHOLE_HEADER_SIZE =
    FS_RAS_HEADER_SIZE + FS_DIMENSION_HEADER_SIZE + FS_UNUSED_HEADER_SIZE;

  /** check if a filename is for a compressed file */
  bool
  IsCompressedFilename(const std::string fname);
  /// processes the actual data buffer
  void
  SwapBytesIfNecessary(void * const buffer, const unsigned long numberOfPixels);

  /// examines the direction cosines and creates encapsulation data
  // void MriDirCos();

  void
  WriteHeader();

  void
  WriteData(const void * buffer);

  void
  PermuteFrameValues(const void * buffer, char * tempmemory);

  unsigned int
  GetComponentSize() const override;

  std::string
  GetOrientation(itk::Matrix<double> directions);

  bool          m_IsCompressed;
  gzFile        m_GZFile;
  std::ofstream m_Output;

  // Utility function to assist with writing to disk in the
  // proper format.  TInType is static_cast<TDiskType> type.
  template <typename TInType, typename TDiskType>
  int
  TWrite(const TInType inValue);
  template <typename TDiskType, typename TOutType>
  int
  TRead(TOutType & outValue);

  int
  TWrite(const char * buf, const unsigned long count);
  void
  OpenFile();
  void
  CloseFile();
};
} // end namespace itk

#endif // itkMGHImageIO_h
