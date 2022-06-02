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

#include "itkMGHImageIOFactory.h"
#include "itkRandomImageSource.h"
#include "itkImageFileReader.h"
#include "itksys/SystemTools.hxx"
#include "itkMetaDataObject.h"
#include "itkIOCommon.h"

#include "itkIOTestHelper.h"
#include "itkMGHImageIOTest.h"
#include <iomanip>

int
itkMGHImageIOTest(int argc, char * argv[])
{
  itk::ObjectFactoryBase::UnRegisterAllFactories();
  itk::MGHImageIOFactory::RegisterOneFactory();
  if (argc < 3)
  {
    std::cerr
      << "ERROR:  Incorrect number of arguments <TestDirectory> <TestMode> [ImageFileNameRead ImageFileNameWrite]"
      << std::endl;
    std::cerr << "Only " << argc << " arguments given." << std::endl;
    return EXIT_FAILURE;
  }
  for (int i = 0; i < argc; ++i)
  {
    std::cout << i << "  argv= " << argv[i] << std::endl;
  }
  //
  // first argument is passing in the writable directory to do all testing
  itksys::SystemTools::ChangeDirectory(argv[1]);

  static bool firstTime = true;
  if (firstTime)
  {
    itk::ObjectFactoryBase::RegisterFactory(itk::MGHImageIOFactory::New());
    firstTime = false;
  }
  const std::string TestMode(argv[2]);

  bool returnSucceeded = true;
  if (TestMode == std::string("FactoryCreationTest"))
  // Tests added to increase code coverage.
  {
    itk::MGHImageIOFactory::Pointer MyFactoryTest = itk::MGHImageIOFactory::New();
    if (MyFactoryTest.IsNull())
    {
      returnSucceeded &= false;
    }
    // This was made a protected function.  MyFactoryTest->PrintSelf(std::cout,0);
  }
  else if (TestMode == std::string("TestReadWriteOfSmallImageOfAllTypes"))
  {
    std::string fn("test.mgz");
    // TODO: Need to test with images of non-identity direction cosigns, spacing, origin
    returnSucceeded &= itkMGHImageIOTestReadWriteTest<unsigned char, 3>(fn, 3, "null", true);
    returnSucceeded &= itkMGHImageIOTestReadWriteTest<short int, 3>(fn, 3, "null", true);
    returnSucceeded &= itkMGHImageIOTestReadWriteTest<int, 3>(fn, 3, "null", true);
    returnSucceeded &= itkMGHImageIOTestReadWriteTest<float, 3>(fn, 3, "null", true);
    returnSucceeded &= itkMGHImageIOTestReadWriteTest<itk::DiffusionTensor3D<float>, 3>(fn, 3, "null", true);
  }
  else if (TestMode == std::string("ReadImagesTest")) // This is a mechanism for reading unsigned int images for
                                                      // testing.
  {
    using ImageType = itk::Image<int, 3>;
    const std::string imageToBeRead(argv[3]);
    const std::string imageToBeWritten(argv[4]);
    try
    {
      std::cout << "Reading Image: " << imageToBeRead << std::endl;
      ImageType::Pointer input = itk::IOTestHelper::ReadImage<ImageType>(imageToBeRead);
      std::cout << input << std::endl;
      itk::ImageFileWriter<ImageType>::Pointer testFactoryWriter = itk::ImageFileWriter<ImageType>::New();
      testFactoryWriter->SetFileName(imageToBeWritten);
      testFactoryWriter->SetInput(input);
      testFactoryWriter->Update();
      itk::ImageFileReader<ImageType>::Pointer testFactoryReader = itk::ImageFileReader<ImageType>::New();
      testFactoryReader->SetFileName(imageToBeWritten);
      testFactoryReader->Update();
      ImageType::Pointer new_image = testFactoryReader->GetOutput();
    }
    catch (itk::ExceptionObject & e)
    {
      e.Print(std::cerr);
      returnSucceeded &= false;
    }
  }
  else if (TestMode == "TestOriginWriteTest")
  {
    using ImageType = itk::Image<int, 3>;
    ImageType::Pointer input;
    const std::string  imageToBeRead(argv[3]);
    const std::string  imageToBeWritten(argv[4]);
    try
    {
      std::cout << "Reading Image: " << imageToBeRead << std::endl;
      input = itk::IOTestHelper::ReadImage<ImageType>(imageToBeRead);
      std::cout << input << std::endl;

      ImageType::PointType reference_origin;
      reference_origin[0] = -123.4;
      reference_origin[1] = 456.7;
      reference_origin[2] = -890.0;
      input->SetOrigin(reference_origin);

      itk::ImageFileWriter<ImageType>::Pointer testFactoryWriter = itk::ImageFileWriter<ImageType>::New();

      testFactoryWriter->SetFileName(imageToBeWritten);
      testFactoryWriter->SetInput(input);
      testFactoryWriter->Update();
      itk::ImageFileReader<ImageType>::Pointer testFactoryReader = itk::ImageFileReader<ImageType>::New();
      testFactoryReader->SetFileName(imageToBeWritten);
      testFactoryReader->Update();
      ImageType::Pointer         new_image = testFactoryReader->GetOutput();
      const ImageType::PointType test_origin = new_image->GetOrigin();
      const double               dist = reference_origin.EuclideanDistanceTo(test_origin);
      if (dist > 1.0E-4)
      {
        std::cerr << std::setprecision(10) << "Origin written and origin read do not match: "
                  << "written: " << reference_origin << " read: " << test_origin << " distance: " << dist << std::endl;
        returnSucceeded &= false;
      }
    }
    catch (itk::ExceptionObject & e)
    {
      e.Print(std::cerr);
      returnSucceeded &= false;
    }
  }
  else
  {
    std::cerr << "Invalid TestMode : " << TestMode << std::endl;
    returnSucceeded &= false;
  }
  return (returnSucceeded == true) ? EXIT_SUCCESS : EXIT_FAILURE;
}
