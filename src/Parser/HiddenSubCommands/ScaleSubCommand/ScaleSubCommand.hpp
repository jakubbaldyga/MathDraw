#pragma once
#include "../../SubCommand/SubCommand.hpp"

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Hidden scale subcommand to call from console.
* \details **Description:**<br>
*		  Provides functionality to call the scale method from console, which scales the given image<br>
*		  Call with --help for more details and available commands<br>
*		  \code{.bash}
*		  MathDraw hidden scale --help
*		  \endcode
*		  Usage:
*		  \code{.bash}
*		  MathDraw hidden scale -i <path to image> -w <width> -he <height> -o <output file>
*		  \endcode
*/
class ScaleSubCommand: public SubCommand
{
public:
	/// @brief Default constructor
	///	
	/// @details Call with scale <br>
	///			 Adds all arguments to the parser<br>
	///			 -i --image <path to image> - path to image to scale<br>
	///			 -w --width <width> - width of the image<br>
	///			 -he --height <height> - height of the image<br>
	///			 -o --output <output> - output file, default is scaledImage.png
	ScaleSubCommand();

	/// @brief scales image and generates output image
	void doCommand() override;
};

