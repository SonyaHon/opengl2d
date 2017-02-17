#ifndef INC_2DS_UTILS_H
#define INC_2DS_UTILS_H

inline double map_value(double input, double input_start, double input_end, double output_start, double output_end) {
	return (output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start));
}

inline double square_distance(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

inline int manhattan_distance(int x1, int y1, int x2, int y2) {
	return (x2 - x1) + (y2 - y1);
}

#endif //INC_2DS_UTILS_H
