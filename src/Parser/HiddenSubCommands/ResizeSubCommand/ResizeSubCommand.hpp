#pragma once
#include "../../SubCommand/SubCommand.hpp"

/**
* \author Jakub Baldyga
* \date 6/01/2024
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Hidden scale subcommand to call from console.
* \details **Description:**<br>
*		  Provides functionality to call the resize method from console, which resizes the given image<br>
*		  Call with --help for more details and available commands<br>
*		  \code{.bash}
*		  MathDraw hidden resize --help
*		  \endcode
*		  Usage:
*		  \code{.bash}
*		  MathDraw hidden resize -i <path to image> -w <width> -he <height> -o <output file>
*		  \endcode
*/
class ResizeSubCommand : public SubCommand
{
public:
	/// @brief Default constructor
	///	
	/// @details Call with resize <br>
	///			 Adds all arguments to the parser<br>
	///			 -i --image <path to image> - path to image to resize<br>
	///			 -w --width <width> - width of the image<br>
	///			 -he --height <height> - height of the image<br>
	///			 -o --output <output> - output file, default is resizedImage.png
	ResizeSubCommand();

	/// @brief resizes image and generates output image
	void doCommand() override;
};