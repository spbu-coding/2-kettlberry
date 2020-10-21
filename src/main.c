#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 100

extern void sort(long long *array_to_sort, int array_length);

struct interval_t {
	long long from;
	long long to;
	int count_from;
	int count_to;
};

int parse_parameters(int argc, char **argv, struct interval_t *interval) {
	if (argc < 2)
		return -1;
	if (argc > 3)
		return -2;

	for (int i = 1; i < argc; i++) {
		if (strncmp(argv[i], "--from=", 7) == 0) {
			interval->count_from++;
			interval->from = strtoll(argv[i] + 7, NULL, 10);
		}
		if (strncmp(argv[i], "--to=", 5) == 0) {
			interval->count_to++;
			interval->to = strtoll(argv[i] + 5, NULL, 10);
		}
    }
	if ((interval->count_to > 1) || (interval->count_from > 1))
		return -3;
	if ((interval->count_to == 0) && (interval->count_from == 0))
		return -4;
	return 0;
}

int read_array(long long *array, struct interval_t interval) {
	int array_size = 0, stdout_size = 0, stderr_size = 0;
	char space;
	long long numbers_in_stdout[MAX_ARRAY_SIZE] = {0}, numbers_in_stderr[MAX_ARRAY_SIZE] = {0};
	long long number;
	do {
		scanf("%lli%c", &number, &space);
		if ((interval.count_from != 0) && (number <= interval.from))
			numbers_in_stdout[stdout_size++] = number;
		if ((interval.count_to != 0) && (number >= interval.to))
			numbers_in_stderr[stderr_size++] = number;
		if (((interval.count_from == 0) || (number > interval.from)) && ((interval.count_to == 0) || (number < interval.to)))
			array[array_size++] = number;
	} while (space == ' ');
	for (int i = 0; i < stdout_size; i++)
		fprintf(stdout, "%lli ", numbers_in_stdout[i]);
	for (int i = 0; i < stderr_size; i++)
		fprintf(stderr, "%lli ", numbers_in_stderr[i]);
	return array_size;
}
void copy_array(long long *array, long long *copied_array, int array_size) {
	for (int i = 0; i < array_size; i++)
		copied_array[i] = array[i];
}
int compare_arrays(long long *array, long long *copied_array, int array_size) {
	int count_different_numbers = 0;
	for (int i = 0; i < array_size; i++)
		if (array[i] != copied_array[i])
			count_different_numbers++;
	return count_different_numbers;
}


int main(int argc, char **argv) {
	struct interval_t interval = {0, 0, 0, 0};
	int parse_parameters_result = parse_parameters(argc, argv, &interval);
	if (parse_parameters_result != 0)
		return parse_parameters_result;
	long long array[MAX_ARRAY_SIZE];
	int array_size;
	array_size = read_array(array, interval);
	long long copied_array[MAX_ARRAY_SIZE];
	copy_array(array, copied_array, array_size);
    sort(array, array_size);
    return compare_arrays(array, copied_array, array_size);
}