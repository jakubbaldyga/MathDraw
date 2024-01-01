#pragma once
#include "../SubCommand/SubCommand.h"

/**
* \author Jakub Baldyga
* \date 16/12/2023
* \copyright (c) 2023 Jakub Baldyga, MIT License
* \brief Recognise subcommand to call from console.
* \details **Description:**<br>
*		  Provides functionality to call the recognise method from console, which recognises number from given image<br>
*		  Call with --help for more details and available commands<br>
*		  \code{.bash}
*		  MathDraw hidden traverse --help
*		  \endcode
*		  Usage:
*		  \code{.bash}
*		  MathDraw recognise -i <path to image> -m <path to model> -n <number system of numbers in the image>
*		  \endcode
*/
class RecogniseSubCommand : public SubCommand
{
	public:
	/// @brief Default constructor
	///	
	/// @details Call with recognise.<br>
	///			 Adds all arguments to the parser.<br>
	///			 -i --image <path to image> - path to image to recognise<br>
	///			 -m --model <path to model> - path to model to use, default "<path to MathDraw.exe>/model.pt"<br>
	///			 -n --number_system <number system> - number system to use, default 10
	/// 
	RecogniseSubCommand();

	/// @brief recognises number from image and prints output
	void doCommand() override;
};