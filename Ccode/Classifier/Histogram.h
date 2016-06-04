// Olga Souverneva 2016

#ifndef _HISTOGRAM_H
#define _HISTOGRAM_H
#include <iostream>

#include "KDE.h"

// Simple Histogram utility classs
template <class T, int Bins>
class Histogram
{
public:
	// Constructor
	Histogram(T start, T end) : Start(start), Width((end-start)/Bins)
	{
		Reset();
	}
	
	// Add a sample to the histogram
	void AddSample(T sample)
	{
		// Add sample to the correct histogram bin
		for (int i=0; i<Bins; i++)
		{
			if (sample >= (Start + (Width * i)) && sample < (Start + (Width * (i+1))))
			{
				m_count[i]++;
				m_total++;
				return;
			}
		}
		
		// Check for sample outside of histogram range
		if (sample < Start)
			m_countTooLow++;
		else
			m_countTooHigh++;
	}
	
	virtual void Reset()
	{
		for (int i=0; i<Bins; i++)
			m_count[i] = 0;
		
		m_countTooLow = 0;
		m_countTooHigh = 0;
		m_total = 0;
	}
	
	// Output scaled such that total*width = 1. For now just assume range is 1 if not using KDE.
	void Output(T* pOut, bool printCout, bool useKDE=false)
	{
		if (pOut == NULL || m_total <= 0)
			return;
		
		if (printCout)
			std::cout << " Histogram: \n";

		if (useKDE)
		{
			KDE* kde = new KDE();
			kde->set_kernel_type(3);
			
			for (int i=0; i<Bins; i++)
			{
				double data = Start + (Width * i) + Width/2;
				for (int j=0; j<m_count[i]; j++)
					kde->add_data(data);
			}
			for (int i=0; i<Bins; i++)
			{
				float x = Start + (Width * i);
				pOut[i] = static_cast<float>(kde->pdf(x));
				if (printCout)
					std::cout << x << ", " << pOut[i] << "\n";
			}

			delete kde;
			return;
		}

		// Output the histogram starting with the smallest bin
		for (int i=0; i<Bins; i++)
		{
			pOut[i] = static_cast<float>(m_count[i]*Bins)/m_total;
			if (printCout)
				std::cout << Start + (Width * i) << ", " << m_count[i] << "\n";
		}
		
		// Output any histogram graph outliers
		if (printCout)
		{
			if (m_countTooLow != 0)
				std::cout << "Too Low: " << m_countTooLow << "\n";
			if (m_countTooHigh != 0)
				std::cout << "Too High: " << m_countTooHigh << "\n";
		}
	}

	T GetWidth(){return Width;}

private:
	// Histogram count array
	int m_count[Bins];

	// The start
	const T Start;

	// The width
	const T Width;

	// Outliers
	int m_countTooLow;
	int m_countTooHigh;
	int m_total;
};


#endif