#ifndef INC_2DS_UTILS_H
#define INC_2DS_UTILS_H

double map_value(double input, double input_start, double input_end, double output_start, double output_end) {
	double output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
	return output;
}

#endif //INC_2DS_UTILS_H
