#include "base.h"

namespace Geometry
{
	struct PuzzlePart
	{
		bool busy;
		int number;

		vector<VolPart> parts;
		PuzzlePart():number(0),busy(false){}
		PuzzlePart(int n):number(n),busy(false){}
		PuzzlePart& rotate(RotType rot)
		{
			for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
			{
				(*it).rotate(rot);
			}
			return *this;
		}
		PuzzlePart& rotate(Mat rot)
		{
			for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
			{
				(*it).rotate(rot);
			}
			return *this;
		}
		void print() const
		{
			cout<<"Part number "<<number<<":"<<endl;
			for (vector<VolPart>::const_iterator it = parts.cbegin(); it != parts.cend(); it++)
			{
				cout<<*it<<endl<<endl;
			}
		}
		bool operator == (const PuzzlePart& part) const
		{
			return parts == part.parts;
		}
		void getBBox(BBox& box) const 
		{
			for (vector<VolPart>::const_iterator it = parts.cbegin(); it != parts.cend(); it++)
			{
				box.merge((*it).xyz);
			}
			return;
		}
		PuzzlePart& shift(const IntVector& shift)
		{
			for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
			{
				(*it).xyz = (*it).xyz + shift;
			}
			return *this;
		}
		Mat getLCS()
		{
			IntVector x = parts[1].xyz - parts[0].xyz;
			IntVector y = parts[2].xyz - parts[0].xyz;
			return Mat(x,y,x.cross(y));
		}

		IntVector getZero()
		{
			return parts[0].xyz;
		}

		PuzzlePart& centralize()
		{
			BBox box;
			getBBox(box);
			shift(-box.minV);
			return *this;
		}
		PuzzlePart copy() const
		{
			return PuzzlePart(*this);
		}
	};
}