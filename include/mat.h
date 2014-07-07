namespace Geometry
{
	struct Mat
	{
		double ar[9];
		inline const double el(int i, int j) const
		{
			return ar[i*3 + j];
		}
		inline double& el(int i, int j)
		{
			return ar[i*3 + j];
		}
		double det()const
		{
			return el(0,0)*el(1,1)*el(2,2)+el(1,0)*el(2,1)*el(0,2)+el(0,1)*el(1,2)*el(2,0) - el(2,0)*el(1,1)*el(0,2)-el(1,0)*el(0,1)*el(2,2)-el(2,1)*el(1,2)*el(0,0);
		}
		void scale(double val)
		{
			for (int i =0; i <9; i++) 
			{
				double r = ar[i] * val;
				ar[i] = r;
				//BREAK_ON_LINE(ar[i] == r);
			}
		}
		Mat(){}
		Mat(IntVector v1,IntVector v2, IntVector v3)
		{
			el(0,0) = v1[0];
			el(1,0) = v1[1];
			el(2,0) = v1[2];

			el(0,1) = v2[0];
			el(1,1) = v2[1];
			el(2,1) = v2[2];

			el(0,2) = v3[0];
			el(1,2) = v3[1];
			el(2,2) = v3[2];
		}
		Mat inverse()
		{
			Mat inv;
			inv.el(0,0) = (el(1,1) * el(2,2) - el(1,2) * el(2,1));
			inv.el(0,1) = (el(0,2) * el(2,1) - el(0,1) * el(2,2));
			inv.el(0,2) = (el(0,1) * el(1,2) - el(0,2) * el(1,1));

			inv.el(1,0) = (el(1,2) * el(2,0) - el(1,0) * el(2,2));
			inv.el(1,1) = (el(0,0) * el(2,2) - el(0,2) * el(2,0));
			inv.el(1,2) = (el(0,2) * el(1,0) - el(0,0) * el(1,2));

			inv.el(2,0) = (el(1,0) * el(2,1) - el(1,1) * el(2,0));
			inv.el(2,1) = (el(0,1) * el(2,0) - el(0,0) * el(2,1));
			inv.el(2,2) = (el(0,0) * el(1,1) - el(0,1) * el(1,0));
			inv.scale(1./det());
			return inv;
		}
		bool operator == (const Mat& m) const
		{
			for (int i=0;i<9;i++)
			{
				if (ar[i] != m.ar[i]) return false;
			}
			return true;
		}
		Mat operator * (const Mat& m) const
		{
			Mat n;
			for (int i=0;i<3;i++)
			{
				for (int j=0;j<3;j++)
				{
					n.el(i,j) = el(i,0) * m.el(0,j) + el(i,1) * m.el(1,j) + el(i,2) * m.el(2,j);
				}
			}
			return n;
		}
	};
}