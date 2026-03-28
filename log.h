#ifndef LOG_H
#define LOG_H

#define DEFAULT   "\033[0m"     //Reset log text color to the default value
#define RED       "\033[31m"    //Set log text color to red

//In an actual embedded system you would want to reduce the size of the prefix information (file name, function name, line number) to save memory.

/*
LOG_INFO() parameters are the string format (fmt) and any VARIADIC ARGUMENTS (...).
"I:%s:%d: " fmt,    formats the log to have log type, file name, function name, line number, then the actual log the user wants to print
## __VA_ARGS__,     ## allows you to print without any arguments. __VA_ARGS__ prints all the arguements from LOG_INFO().
You can also encapsulate fprintf inside of a do while(0) loop if you need to execute multiple lines of code inside of the LOG_INFO macros.
*/
#define LOG_INFO_N(fmt, ...)    fprintf(stderr, "I:%s:%s():%d: " fmt "\n", __FILE__, __func__, __LINE__, ## __VA_ARGS__)
#define LOG_INFO(fmt, ...)      fprintf(stderr, "I:%s:%s():%d: " fmt, __FILE__, __func__, __LINE__, ## __VA_ARGS__)

#define LOG_ERROR_N(fmt, ...)    fprintf(stderr, RED "E:%s:%s():%d: " fmt "\n" DEFAULT, __FILE__, __func__, __LINE__, ## __VA_ARGS__)
#define LOG_ERROR(fmt, ...)      fprintf(stderr, RED "E:%s:%s():%d: " fmt DEFAULT, __FILE__, __func__, __LINE__, ## __VA_ARGS__)

#endif //LOG_H