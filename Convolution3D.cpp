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
	//maskenin 2D yapýlmasý
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
		}//RGB pixel olarak diziye alýndý 1D to 3D transform
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
