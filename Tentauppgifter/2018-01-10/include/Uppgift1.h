#ifndef UPPGIFT1_h
#define UPPGIFT1_h

#include <string>
#include <map>

struct PictureData
{
	int width, height;
	unsigned int* pixels;
};

class Picture
{
	public:
		Picture(std::string filename)
		{
			data = new PictureData();
			//data->width = // läster in width
			//data->height = // läster in height
			data->pixels = new unsigned int[data->width * data->height];
			counts[data] = 1;
		}

		Picture(const Picture& other) : data(other.data)
		{
			counts[data]++;
		}

		const Picture operator=(const Picture& other)
		{
			// Tilldelningsoperator måste kolla om data är lika med den andra datan.
			// om den INTE är det så måste ju den gammla datan raderas innan den tilldelas den nya,
			// annars får vi ett minnesläckage
			if(data != other.data)
			{
				if(--counts[data] == 0)
				{
					delete [] data->pixels;
					delete data;
					counts.erase(data);
				}
				data = other.data;
				counts[data]++;
			}

			return *this;
		}

		~Picture()
		{
			if(--counts[data] == 0)
			{
				delete [] data->pixels;
				delete data;
				counts.erase(data);
			}
		}


	private:
		PictureData* data;
		static std::map<PictureData*, int> counts;
};

#endif