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

#ifndef itkMGHImageIOFactory_h
#define itkMGHImageIOFactory_h

#include "itkObjectFactoryBase.h"
#include "itkImageIOBase.h"

#include "MGHIOExport.h"

namespace itk
{
/** \class MGHImageIOFactory
 * \brief Create instances of MGHImageIO objects using an object factory.
 * \ingroup MGHIO
 */
class MGHIO_EXPORT MGHImageIOFactory : public ObjectFactoryBase
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(MGHImageIOFactory);

  /** Standard class type alias */
  using Self = MGHImageIOFactory;
  using Superclass = ObjectFactoryBase;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Class methods used to interface with the registered factories **/
  const char *
  GetITKSourceVersion() const override;

  const char *
  GetDescription() const override;

  /** Method for class instantiation **/
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(MGHImageIOFactory);

  /** Register one factory of this type */
  static void
  RegisterOneFactory()
  {
    MGHImageIOFactory::Pointer MGHFactory = MGHImageIOFactory::New();

    ObjectFactoryBase::RegisterFactoryInternal(MGHFactory);
  }

protected:
  MGHImageIOFactory();
  ~MGHImageIOFactory() override;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;
};
} // end namespace itk

#endif /// itkMGHImageIOFactory_h
