double* Convolution3D(BYTE* Buffer, int Width, int Height, double* Mask, int m_w, int m_h)
{
	int sum = 0,cur,channel = 3;
	int w_new = Width - (m_w - 1);
	int h_new = Height - (m_h - 1);

	double*** C3Dbuf = new double** [channel];
	for (int i = 0; i < channel; i++)
	{
		C3Dbuf[i] = new double* [Height];
		for (int j = 0; j < Height; j++)
		{
			C3Dbuf[i][j] = new double[Width];
		}
	}
	double*** C3Dnewbuf = new double** [channel];
	for (int i = 0; i < channel; i++)
	{
		C3Dnewbuf[i] = new double* [h_new];
		for (int j = 0; j < h_new; j++)
		{
			C3Dnewbuf[i][j] = new double[w_new];
		}
	}
	//3dbuf[i][j][k];
	double** Maske = new double* [m_h];
	double* tekbuf = new double[w_new * h_new * channel];
	for (int i = 0; i < m_h; i++)
	{
		Maske[i] = new double[m_w];
	}
	//maskenin 2D yap�lmas�
	for (int row = 0; row < m_h; row++)
	{
		for (int column = 0; column < m_w; column++)
		{
			int matemp = row * m_w + column;
			Maske[(matemp - column) / m_w][column] = Mask[matemp];
		}
	}
	
		for (int row = 0; row < Height; row++)
		{
			for (int col = 0; col < Width; col++)
			{
				for (int k = 0; k < channel; k++)
				{
					cur = row * Width + col;
					C3Dbuf[k][row][col] = Buffer[channel * cur + k];
				}
			}
		}//RGB pixel olarak diziye al�nd� 1D to 3D transform
	//convolution
	for (int d = 0; d < channel; d++)
	{
		for (int i = 0; i < h_new; i++)
		{
			for (int j = 0; j < w_new; j++)
			{
				for (int a = i; a < i + m_h; a++)
				{
					for (int b = j; b < j + m_w; b++)
					{
						sum += (C3Dbuf[d][a][b] * Maske[a - i][b - j]);
					}
				}
				C3Dnewbuf[d][i][j] = abs(sum);
				sum = 0;
			}
		}
	}
	
		for (int i = 0; i < h_new; i++)
		{
			for (int j = 0; j < w_new; j++)
			{
				for (int k = 0; k < channel; k++)
				{
					cur = i * w_new + j;
					tekbuf[channel * cur + k] = C3Dnewbuf[k][i][j];
				}
			}
		}//3D to 1D transform
	return tekbuf;

}


//with padding
double* Convolution3DWithPadding(BYTE* Buffer, int Width, int Height, double* Mask, int m_w, int m_h)
{
	int sum = 0, tep, padw, padh,channel = 3;
	padw = (m_w - 1) / 2;
	padh = (m_h - 1) / 2;
	int w_new = Width + 2 * padw;//p padding de�eri p = f-1/2 f = mask size
	int h_new = Height + 2 * padh;//picture is the same size but buf into the mask n+2*p 


	double** Maske = new double* [m_w];
	double* tekbuf = new double[Width * Height * channel];
	for (int i = 0; i < m_h; i++)
	{
		Maske[i] = new double[m_w];
	}

	double*** C3Dbuf = new double** [channel];
	for (int i = 0; i < channel; i++)
	{
		C3Dbuf[i] = new double* [h_new];
		for (int j = 0; j < h_new; j++)
		{
			C3Dbuf[i][j] = new double[w_new];
		}
	}
	double*** C3Dtempbuf = new double** [channel];
	for (int i = 0; i < channel; i++)
	{
		C3Dtempbuf[i] = new double* [Height];
		for (int j = 0; j < Height; j++)
		{
			C3Dtempbuf[i][j] = new double[Width];
		}
	}
	//3dbuf[i][j][k]


	//maskenin 2 boyuta �evrilmesi
	for (int row = 0; row < m_h; row++)
	{
		for (int column = 0; column < m_w; column++)
		{
			int matemp = row * m_w + column;
			Maske[(matemp - column) / m_w][column] = Mask[matemp];
		}
	}
	for (int row = 0; row < h_new; row++)
	{
		for (int column = 0; column < w_new; column++)
		{
			for (int k = 0; k < channel; k++)
			{
				C3Dbuf[k][row][column] = 0;
			}
		}
	}

	for (int row = padh / 2; row < (padh / 2) + Height; row++)
	{
		for (int column = padw / 2; column < (padw / 2) + Width; column++)
		{
			tep = (row - (padh / 2)) * Width + (column - padw / 2);
			for (int k = 0; k < channel; k++)
			{
				C3Dbuf[k][row][column] = Buffer[channel*tep+k];
			}
		}
	}

	for (int d = 0; d < channel; d++)
	{
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				for (int a = i; a < i + m_h; a++)
				{
					for (int b = j; b < j + m_w; b++)
					{
						sum += (C3Dbuf[d][a][b] * Maske[a - i][b - j]);
					}
				}
				C3Dtempbuf[d][i][j] = abs(sum);
				sum = 0;
			}
		}
	}
	

	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			for (int k = 0; k < channel; k++)
			{
				tekbuf[channel * tep + k] = C3Dtempbuf[k][row][column];
			}
		}
	}
	return tekbuf;
}

