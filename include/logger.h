#ifndef LOGGER_H
#define LOGGER_H

//
char* get_log_file_name();

// Read / write operations
void add_to_log(const char* message, ...);
void read_log(const char* title);
void clear_log();

// Open / close operations
void open_logger(const char* file_name);
void close_logger();

void logger_demo();

#endif // LOGGER_H
