#ifndef LOGGER_H
#define LOGGER_H

void set_log_file(char* file_name);
char* get_log_file_name();
void add_to_log(char* message, ...);
void read_log();
void clear_log();
int push_filename();
int pop_filename();
void logger_demo();

#endif // LOGGER_H
