#pragma once
#include "../../SubCommand/SubCommand.h"

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Hidden traverse subcommand to call from console.
* \details **Description:**<br>
*		  Provides functionality to call the traverse method from console,<br>
*		  which traverse the given image<br><br>
*		  Call with --help for more details and available commands<br>
*		  \code{.bash}
*		  MathDraw hidden traverse --help
*		  \endcode
*		  Usage:
*		  \code{.bash}
*		  MathDraw hidden traverse
*		  \endcode
*/
class TraverseSubCommand: public SubCommand
{
public:
	/// @brief Default constructor
	///	
	/// @details Call with traverse<br>
	///			 Adds all arguments to the parser<br>
	///			 -i --image <path to image> - path to image to traverse<br>
	///			 -o --output <output> - output file, default is traversedImage.png. Adds number to the end of the file name. For example traversedImage0.png
	TraverseSubCommand();

	/// @brief traverses image and generates output images
	void doCommand() override;

};

