@page cli Command line interface

MathDraw also provides command line interface. Check it out.

##Short example
Here is a short example, to show you how simple it is to use:
\code{.bash}
	MathDraw recognise -i "image.png"
\endcode


##Tutorial

###For help call:
\code{.bash}
	MathDraw --help
\endcode

###For help regarding to any subcommand, call:
\code{.bash}
	MathDraw subcommand --help
\endcode

###There is one command available to everyone:
It recognises the digits on given image and prints them.
\code{.bash}
	MathDraw recognise
\endcode
It has 3 arguments:
	- -i --image <path to image> - path to image to recognise, required
	- -m --model <path to model> - path to model to use, "<path to MathDraw.exe>\model.pt" by default
	- -n --number_system <number system> - number system to use, 10 by default


##For developers
There are also functions which are hidden.
To see them all, call:
\code{.bash}
	MathDraw hidden --help
\endcode

###For now there are 3 commands available:
####Scale subcommand
It scales the given image to the given dimensions.
 \code{.bash}
	 MathDraw hidden scale
 \endcode
 It has 4 arguments:
	- -i --image <path to image> - path to image to scale
	- -w --width <width> - width of the image
	- -h --height <height> - height of the image
	- -o --output <output> - output file, default is scaledImage.png

####Traverse subcommand
It detects and extracts lighter parts of the image to different images. It is used to separate each digit.
  \code{.bash}
	 MathDraw hidden traverse
 \endcode
 It has 2 arguments:
	- -i --image <path to image> - path to image to scale
	- -o --output <output> - output file, default is traversedImage.png. Adds number to the end of the file name. For example traversedImage0.png