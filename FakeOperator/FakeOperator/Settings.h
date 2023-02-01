#pragma once // means header files are only compiled once... (dont delete this line again..)


// Average amount of time between keypress at 190 characters per minute
int const AVTIME = 315;
// Load time
int const LOADTIME = 1000;
// Callback time
int const CALL2SERVER = 60000;

// Used for mouse moving
int horizontal = 0;
int vertical = 0;


// Windows focusing and handles
std::string WindowFocus;
static const HANDLE InvalidValue = NULL;
