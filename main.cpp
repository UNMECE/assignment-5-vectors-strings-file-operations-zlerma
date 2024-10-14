// Zaid Orozco-Lerma
// Assignment 5

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"

void average_colors(const std::vector<Pixel> &pixel_list);

void flip_vertically(std::vector<Pixel> &pixel_list);

int main(int argc, char* argv[]) {

	// If the filename is not provided, give an error message.
	if (argc < 2) {
		std::cerr << "UH OH! No filename input as command line argument!" << std::endl;
		return 1; // Return with error code
	}

	// If the filename is provided, we proceed.
	std::string filename = argv[1];

	// Here is our vector called pixel_list, "which will store every pixel read in the from the file."
	std::vector<Pixel> pixel_list;

	std::ifstream infile(filename);
	if (!infile)
	{
		// Some error handling for file opening errors
		std::cerr << "Error opening file " << filename << std::endl;
		return 1;
	}

	// Here we are reading each line...
	std::string line;
	while (std::getline(infile, line))
	{
		// I made a pixel object here for storing values
		Pixel pixel;

		// We need some variables to hold positions while parsing
		size_t pos = 0;	   // 1st, current position of the delimiter
		size_t prev_pos = 0;  // 2nd, starting position of the substring

		try
		{
			// X-coordinate
			pos = line.find(',', prev_pos);			   // Find the position of the first comma
			if (pos == std::string::npos) continue;	   // If no comma is found, skip to the next line
			pixel.x = std::stoi(line.substr(prev_pos, pos - prev_pos)); // Convert substring to integer
			prev_pos = pos + 1;						   // Update previous position for the next parse

			// Y-coordinate
			pos = line.find(',', prev_pos);
			if (pos == std::string::npos) continue;
			pixel.y = std::stoi(line.substr(prev_pos, pos - prev_pos));
			prev_pos = pos + 1;

			// Red
			pos = line.find(',', prev_pos);
			if (pos == std::string::npos) continue;
			pixel.r = std::stof(line.substr(prev_pos, pos - prev_pos)); // Convert substring to float
			prev_pos = pos + 1;

			// Green
			pos = line.find(',', prev_pos);
			if (pos == std::string::npos) continue;
			pixel.g = std::stof(line.substr(prev_pos, pos - prev_pos));
			prev_pos = pos + 1;

			// Blue
			pixel.b = std::stof(line.substr(prev_pos)); // Convert the remaining substring to float

			// Add the pixel to the pixel_list vector
			pixel_list.push_back(pixel);
		}
		catch (const std::exception& e)
		{
			// Some error handling for parsing
			std::cerr << "Warning: Skipping invalid line: " << line << std::endl;
			continue;
		}

	}

	// Closing the file (after reading the data),
	infile.close();

	// Calculating the average colors,
	average_colors(pixel_list);

	// Flipping the image vertically,
	flip_vertically(pixel_list);

	// And finally, saving the flipped image data --- to "flipped.dat", as specified
	std::ofstream outfile("flipped.dat");
	if (!outfile)
	{
		// Some error handling for opening the NEW file
		std::cerr << "Error opening file flipped.dat for writing" << std::endl;
		return 1;
	}

	// Basically, now we put each pixel into the new file
	for (const auto& pixel : pixel_list)
	{
		outfile << pixel.x << "," << pixel.y << ","
				<< pixel.r << "," << pixel.g << "," << pixel.b << "\n";
	}

	// Close the file (after writing the data)
	outfile.close();

	// Successful program execution! If we get here...
	return 0;
}

// Calculate and display the average of R, G, and B values
void average_colors(const std::vector<Pixel> &pixel_list)
{

	double sum_r = 0.0;
	double sum_g = 0.0;
	double sum_b = 0.0;

	for (const auto& pixel : pixel_list)
	{
		sum_r += pixel.r;
		sum_g += pixel.g;
		sum_b += pixel.b;
	}

	// Calculate the average --- Divide the sums by number of pixels
	size_t n = pixel_list.size(); // Total number of pixels
	if (n == 0)
	{
		std::cerr << "Error: Pixel list is empty." << std::endl;
		return;
	}

	double avg_r = sum_r / n;
	double avg_g = sum_g / n;
	double avg_b = sum_b / n;

	// Display the averages
	std::cout << "Average R: " << avg_r << std::endl;
	std::cout << "Average G: " << avg_g << std::endl;
	std::cout << "Average B: " << avg_b << std::endl;
}

// Flip the image vertically /\ \/ /\ \/
void flip_vertically(std::vector<Pixel> &pixel_list)
{
	// 1st, find the max y-value for image height
	int max_y = 0;
	for (const auto& pixel : pixel_list)
	{
		if (pixel.y > max_y)
		{
			max_y = pixel.y;
		}
	}

	// The image height is max_y + 1
	int image_height = max_y + 1;

	// Iterate over each pixel in the list
	for (auto& pixel : pixel_list)
	{
		// FLIP the y-coordinate /\ \/ /\ \/
		pixel.y = image_height - pixel.y - 1;
	}
}