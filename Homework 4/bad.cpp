// Remove the movies in li with a rating below 55 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBad(list<Movie*>& li)
{
	for (auto p = li.begin(); p != li.end(); p++)
	{
		if ((*p)->rating() < 55)
		{
			delete *p;
			p = li.erase(p);
			p--;
		}
	}
}
