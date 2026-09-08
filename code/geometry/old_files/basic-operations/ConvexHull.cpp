// Author: Gino
vector<Pt> hull;
void convexHull() {
hull.clear(); sort(E.begin(), E.end());
for (int t : {0, 1}) {
    int b = (int)hull.size();
    for (auto& ei : E) {
        while ((int)hull.size() - b >= 2 &&
               ori(mv(hull[(int)hull.size()-2], hull.back()),
                   mv(hull[(int)hull.size()-2], ei)) == -1) {
            hull.pop_back();
        }
        hull.emplace_back(ei);
    }
    hull.pop_back();
    reverse(E.begin(), E.end());
} }
