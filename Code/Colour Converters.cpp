#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<double> cmyk_to_rgb(double cyan, double magenta, double yellow, double black_key) { //Input cyan, magenta, yellowand black key as values from 0 to 1
	double red = 255 * (1 - cyan) * (1 - black_key);
	double green = 255 * (1 - magenta) * (1 - black_key);
	double blue = 255 * (1 - yellow) * (1 - black_key);
	return std::vector<double> {red, green, blue};
}

std::vector<double> rgb_to_cmyk(double red, double green, double blue) { //Input red, greenand blue as values from 0 to 255
	red /= 255;
	green /= 255;
	blue /= 255;
	std::vector<double> rgb_list{ red, green, blue };
	std::sort(rgb_list.begin(), rgb_list.end());
	double black_key = 1 - rgb_list[2];
	rgb_list.~vector();
	double cyan = (1 - red - black_key) / (1 - black_key);
	double magenta = (1 - green - black_key) / (1 - black_key);
	double yellow = (1 - blue - black_key) / (1 - black_key);
	return std::vector<double> {cyan, magenta, yellow, black_key};
}

std::vector<double> rgb_to_hsl(double red, double green, double blue) { //Input red, greenand blue values from 0 to 255
	red /= 255;
	green /= 255;
	blue /= 255;
	double saturation = 0;
	double hue = 0;
	std::vector<double> rgb_list{ red, green, blue };
	std::sort(rgb_list.begin(), rgb_list.end());
	double luminance = (static_cast<double>(rgb_list[0]) + rgb_list[2]) / 2;
	luminance = round(luminance * 100);
	luminance /= 100;
	if (rgb_list[0] == rgb_list[2]) {
		saturation = 0;
	}
	else {
		if (luminance <= 0.5) {
			saturation = (rgb_list[2] - rgb_list[0]) / (rgb_list[2] + rgb_list[0]);
		}
		else {
			saturation = (rgb_list[2] - rgb_list[0]) / (2.0 - rgb_list[2] - rgb_list[0]);
		}
	}
	//saturation = round(saturation, 2);
	if (saturation == 0) {
		hue = 0;
	}
	else {
		if (red == rgb_list[2]) {
			hue = (green - blue) / (rgb_list[2] - rgb_list[0]);
		}
		else if (green == rgb_list[2]) {
			hue = 2.0 + (static_cast<double>(blue) - red) / (rgb_list[2] - rgb_list[0]);
		}
		else if (blue == rgb_list[2]) {
			hue = 4.0 + (red - green) / (rgb_list[2] - rgb_list[0]);
		}
	}
	hue *= 60;
	hue = round(hue);
	rgb_list.~vector();
	return std::vector<double> {hue, saturation, luminance};
}

std::vector<double> hsl_to_rgb(double hue, double saturation, double luminance) {		//Input hue value in degrees(360), saturationand luminance as values from 0 to 1
	if (saturation == 0) {
		double red = luminance * 255;
		double green = luminance * 255;
		double blue = luminance * 255;
		return std::vector<double> {red, green, blue};
	}
	double temporary_1 = 0;
	if (luminance < 0.5) {
		temporary_1 = luminance * (1.0 + saturation);
	}
	else {
		temporary_1 = luminance + saturation - luminance * saturation;
	}
	double temporary_2 = 2 * luminance - temporary_1;
	hue /= 360;
	double temporary_rgb[] = { hue + 0.333, hue, hue - 0.333 };
	for (double& value : temporary_rgb) {
		if (value < 0) {
			value++;
		}
		else if (value > 1) {
			value--;
		}
	}
	double rgb[] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) {
		if (6 * temporary_rgb[i] < 1) {
			rgb[i] = temporary_2 + (temporary_1 - temporary_2) * 6 * temporary_rgb[i];
		}
		else if (2 * temporary_rgb[i] < 1) {
			rgb[i] = temporary_1;
		}
		else if (3 * temporary_rgb[i] < 2) {
			rgb[i] = temporary_2 + (temporary_1 - temporary_2) * (0.666 - temporary_rgb[i]) * 6;
		}
		else {
			rgb[i] = temporary_2;
		}
	}
	for (double& value : rgb) {
		value = (round(value * 255));
	}
	return std::vector<double> {rgb[0], rgb[1], rgb[2]};
}

std::string rgb_to_hex(int red, int green, int blue) { //Input red, green and blue values from 0 to 255
	int hex_value = 0;
	hex_value = red * 0x10000 + green * 0x100 + blue;
	std::stringstream hex_str;
	hex_str << "#" << std::hex << hex_value;
	return hex_str.str();
}

std::vector<int> hex_to_rgb(std::string hex_value) { //Input a string with a hex value(# then 6 - digit hexadecimal value)
	int red = '0x' + hex_value[2, 3];
	int green = '0x' + hex_value[4, 5];
	int blue = '0x' + hex_value[6, 7];
	return std::vector<int> { int(red), int(green), int(blue) };
}

int main() {
	return 0;
}
