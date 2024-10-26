int main() {

    map<int, vector<int> > mp;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
    prqueue<int> pq;
    for (int i = 0; i < n; i++) {
    pq.enqueue(vals[i], prs[i]);
    mp[prs[i]].push_back(vals[i]);
    }
    cout << pq.toString() << endl;
}