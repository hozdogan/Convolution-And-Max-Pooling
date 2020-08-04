BYTE** Max_Pooling1D(BYTE** Buffer,int input_dim)
{
	BYTE* arr = new BYTE[4];//2*2 max pooling
	BYTE max;
	BYTE** newbuf;
	if (input_dim % 2 != 0)
	{
		newbuf = new BYTE * [(input_dim - 1) / 2];
		for (int i = 0; i < (input_dim - 1) / 2;i++)
		{
			newbuf[i] = new BYTE[(input_dim - 1)/2];
		}
		//process
		for (int row = 0; row < input_dim - 1; row+=2)
		{
			for (int col = 0; col < input_dim - 1; col+=2)
			{
				arr[0] = Buffer[row][col];
				arr[1] = Buffer[row][col+1]; 
				arr[2] = Buffer[row+1][col];
				arr[3] = Buffer[row+1][col+1];
				max = findMax(arr, 4);
				newbuf[row / 2][col / 2] = max;
			}
		}
	}
	else if (input_dim % 2 == 0)
	{
		newbuf = new BYTE * [input_dim / 2];
		for (int i = 0; i < input_dim / 2; i++)
		{
			newbuf[i] = new BYTE[input_dim / 2];
		}
		//process
		for (int row = 0; row < input_dim; row += 2)
		{
			for (int col = 0; col < input_dim; col += 2)
			{
				arr[0] = Buffer[row][col];
				arr[1] = Buffer[row][col + 1];
				arr[2] = Buffer[row + 1][col];
				arr[3] = Buffer[row + 1][col + 1];
				max = findMax(arr, 4);
				newbuf[row / 2][col / 2] = max;
			}
		}
	}
	return newbuf;

}
