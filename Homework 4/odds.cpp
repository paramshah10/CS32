void removeOdds(vector<int>& v)
{
	auto i = v.begin();
	while (i != v.end())
	{
		if (*i % 2 != 0)
		{
			v.erase(i);
			i = v.begin();
		}
		i++;
	}
}