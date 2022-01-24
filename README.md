ITKMGHImageIO
=============

![Build, test, package status](https://github.com/InsightSoftwareConsortium/ITKMGHImageIO/workflows/Build,%20test,%20package/badge.svg)
[![PyPI Version](https://img.shields.io/pypi/v/itk-iomgh.svg)](https://pypi.python.org/pypi/itk-iomgh)

ITK remote module for IO of images stored in `mgh`, `mgz` and `mgh.gz` formats.

See https://surfer.nmr.mgh.harvard.edu/fswiki/FsTutorial/MghFormat
    https://surfer.nmr.mgh.harvard.edu/

## History

The original implementation was developed in the Slicer code base (folder `Slicer/Libs/MGHImageIO`)
with contributions from Nicole Aucoin, Steve Pieper, Georghe, Dennis Jen, Bruce Fischl, Sebastien Barre, Jim Miller, Bill Lorensen,
Dominique Belhachemi, Jean-Christophe Fillion-Robin, Julien Finet, Matt McCormick, Hans Johnson, Kent Williams
and Andras Lasso.

In May 2013, Hans Johnson created the repository `Slicer/itkMGHImageIO` enabling ITK
based programs to support reading and writing MGH files. See [Slicer/itkMGHImageIO@4fa1fd815](https://github.com/InsightSoftwareConsortium/ITKMGHImageIO/commit/4fa1fd8155a697bdd1a2c73f475178220d9fb09f). Between 2013 and 2021, this
more general implementation has been developed with contributions from Hans Johnson, Mathew Seng, Xiaoxiao Liu, Matt McCormick, Jon Haitz Legarreta, François Budin, Zach Williamson and Jean-Christophe Fillion-Robin.

In September 2015, starting with Slicer commit [Slicer/Slicer@184e907df](https://github.com/Slicer/Slicer/commit/184e907df), Slicer was updated to use the IO provided by `Slicer/itkMGHImageIO` through the ITK remote module mechanism.

Finally, in December 2021, the project originally created in the `Slicer` GitHub organization was transferred to the `InsightSoftwareConsortium` GitHub organization and re-forked into the Slicer one. The
ITK remote module was also updated to reference the project in the InsightSoftwareConsortium organization. See [InsightSoftwareConsortium/ITK@f84c9ef09](https://github.com/InsightSoftwareConsortium/ITK/commit/f84c9ef0903ff662e6716db2b138509505e85072).

