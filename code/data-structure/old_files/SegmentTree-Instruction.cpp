struct node {
    // define your value and tag here
}

void pull(int cl, int cr, int idx) {
    // Update the answer
    // No other tricks, its easy
}

void push(int l, int r, int idx, int cl, int cr, int mid) {
    /* Important Concept:
         * Every tag records their CHILDREN need to be modify
         * EXCLUDING ITSELF!!!
         * Self has already been modified when assigned tag!
     * 
     * Special Case: Leaf Node (no children)
     * Change first, Addition second
     * 
     * 1. Update children's value
     * 2. Assign the same tag to children
     * 3. Reset self's tag
     */
}

void build(int l, int r, int idx) {
    /* Special Case: Leaf Node
     * Build LEFT
     * Build RIGHT
     * if (NOT LEAF) pull()  // Because pull() needs parameters of children
     */
}

void modify(int ql, int qr, int val, int l, int r, int idx) {
    /* if (current itv not in query) return;
     * if (current itv all in query) {
         * Update value
         * Put tag
         * return;
     * }
     * PUSH()
     * Modify LEFT
     * Modify RIGHT
     * if (NOT LEAF) pull()
     */
}

int query(int ql, int qr, int val, int l, int r, int idx) {
    /* if (current itv not in query) return an unimportant value
     * if (current itv all in query) return self's value
     * PUSH()
     * Ask LEFT
     * Ask RIGHT
     * Decide which to return
     */
}
