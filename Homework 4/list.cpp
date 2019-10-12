
void listAll(const Domain* d, string path) // two-parameter overload
{
	if (d->subdomains().empty())
	{
		cout << path << endl;
		return;
	}

	if (path != "")
		path = '.' + path;
	for (auto k = d->subdomains().begin(); k != d->subdomains().end(); k++)
		listAll(*k, (*k)->label() + path);
}
