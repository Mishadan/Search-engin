#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;


string ReadLine() {
	string s;
	getline(cin, s);
	return s;
}

int ReadLineWithNumber() {
	int result;
	cin >> result;
	ReadLine();
	return result;
}

vector<string> SplitIntoWords(const string& text) {
	vector<string> words;
	string word;
	for (const char c : text) {
		if (c == ' ') {
			words.push_back(word);
			word = "";
		}
		else {
			word += c;
		}
	}
	words.push_back(word);

	return words;
}

set<string> ParseStopWords(const string& text) {
	set<string> stop_words;
	for (const string& word : SplitIntoWords(text)) {
		stop_words.insert(word);
	}
	return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {
	vector<string> words;
	for (const string& word : SplitIntoWords(text)) {
		if (stop_words.count(word) == 0) {
			words.push_back(word);
		}
	}
	return words;
}

void AddDocument(map<string, set<int>>& word_to_documents,
	const set<string>& stop_words,
	int document_id,
	const string& document) {
	for (const string& word : SplitIntoWordsNoStop(document, stop_words)) {
		word_to_documents[word].insert(document_id);
	}
}

vector<pair<int, int>> FindDocuments(const map<string, set<int>>& word_to_documents,
	const set<string>& stop_words,
	const string& query) {
	const vector<string> query_words = SplitIntoWordsNoStop(query, stop_words);
	set<int> document_ids;
	map<int, int> d_to_r;
	for (const string& word : query_words) {
		if (word_to_documents.count(word) == 0) {
			continue;
		}
		for (const int document_id : word_to_documents.at(word)) {
			document_ids.insert(document_id);
			++d_to_r[document_id];
		}
		// � ����� ���:
		// const auto& local_document_ids = word_to_documents.at(word);
		// document_ids.insert(local_document_ids.begin(), local_document_ids.end());
	}
	set<pair<int, int>> result;
	for (int id : document_ids)
	{
		result.emplace(id, d_to_r.at(id));
	}
	vector<pair<int, int>> r(result.begin(), result.end());
	return r;
}


int main() {
	cout << "Stop words : "s << endl;
	const string stop_words_joined = ReadLine();
	const set<string> stop_words = ParseStopWords(stop_words_joined);

	// Read documents
	map<string, set<int>> word_to_documents;
	cout << "Number of documents to add : "s << endl;
	const int document_count = ReadLineWithNumber();
	for (int document_id = 0; document_id < document_count; ++document_id) {
		cout << document_id << " : "s << endl;
		AddDocument(word_to_documents, stop_words, document_id, ReadLine());
	}

	cout << "Search request : "s << endl;
	const string query = ReadLine();
	cout << "Search results : "s;
	//const string query = ReadLine();
	for (auto [document_id, relevance] : FindDocuments(word_to_documents, stop_words, query)) {
		cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s << endl;
	}
	system("pause");
}