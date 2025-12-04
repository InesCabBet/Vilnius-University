// ---------------------------
// Node class
// ---------------------------
class Node {
  constructor(data) {
    this.data = data;
    this.left = null;
    this.right = null;
  }
}

// ---------------------------
// Tree class
// ---------------------------
class Tree {
  constructor(array) {
    this.root = this.buildTree(array);
  }

  // ---------------------------
  // Build balanced BST
  // ---------------------------
  buildTree(array) {
    if (!array.length) return null;
    const sorted = [...new Set(array)].sort((a, b) => a - b);

    const build = (arr, start, end) => {
      if (start > end) return null;
      const mid = Math.floor((start + end) / 2);
      const node = new Node(arr[mid]);
      node.left = build(arr, start, mid - 1);
      node.right = build(arr, mid + 1, end);
      return node;
    };

    return build(sorted, 0, sorted.length - 1);
  }

  // ---------------------------
  // INSERTION
  // ---------------------------
  insert(value) {
    const rec = (node, value) => {
      if (node === null) return new Node(value);
      if (value === node.data) return node; // evitar duplicados
      if (value < node.data) node.left = rec(node.left, value);
      else node.right = rec(node.right, value);
      return node;
    };
    this.root = rec(this.root, value);
  }

  // ---------------------------
  // DELETE
  // ---------------------------
  deleteItem(value) {
    const rec = (node, value) => {
      if (node === null) return null;

      if (value < node.data) {
        node.left = rec(node.left, value);
      } else if (value > node.data) {
        node.right = rec(node.right, value);
      } else {
        // Caso encontrado
        if (!node.left) return node.right;
        if (!node.right) return node.left;

        // dos hijos → usar sucesor inorder
        let successor = node.right;
        while (successor.left) successor = successor.left;
        node.data = successor.data;
        node.right = rec(node.right, successor.data);
      }
      return node;
    };
    this.root = rec(this.root, value);
  }

  // ---------------------------
  // FIND
  // ---------------------------
  find(value) {
    let current = this.root;
    while (current) {
      if (value === current.data) return current;
      current = value < current.data ? current.left : current.right;
    }
    return null;
  }

  // ---------------------------
  // LEVEL ORDER (una línea)
  // ---------------------------
  levelOrder() {
    const result = [];
    const queue = [];
    if (this.root) queue.push(this.root);

    while (queue.length > 0) {
      const node = queue.shift();
      result.push(node.data);
      if (node.left) queue.push(node.left);
      if (node.right) queue.push(node.right);
    }
    return result;
  }

  // ---------------------------
  // DEPTH-FIRST TRAVERSALS (una línea)
  // ---------------------------
  inOrder() {
    const result = [];
    const rec = node => {
      if (!node) return;
      rec(node.left);
      result.push(node.data);
      rec(node.right);
    };
    rec(this.root);
    return result;
  }

  preOrder() {
    const result = [];
    const rec = node => {
      if (!node) return;
      result.push(node.data);
      rec(node.left);
      rec(node.right);
    };
    rec(this.root);
    return result;
  }

  postOrder() {
    const result = [];
    const rec = node => {
      if (!node) return;
      rec(node.left);
      rec(node.right);
      result.push(node.data);
    };
    rec(this.root);
    return result;
  }

  // ---------------------------
  // ALTURA y PROFUNDIDAD
  // ---------------------------
  height(node) {
    if (!node) return -1;
    return 1 + Math.max(this.height(node.left), this.height(node.right));
  }

  depth(value) {
    let current = this.root;
    let depth = 0;

    while (current) {
      if (value === current.data) return depth;
      current = value < current.data ? current.left : current.right;
      depth++;
    }
    return null;
  }

  // ---------------------------
  // BALANCE CHECK
  // ---------------------------
  isBalanced() {
    const check = node => {
      if (!node) return { balanced: true, height: -1 };

      const left = check(node.left);
      const right = check(node.right);

      const balanced =
        left.balanced &&
        right.balanced &&
        Math.abs(left.height - right.height) <= 1;

      return {
        balanced,
        height: 1 + Math.max(left.height, right.height),
      };
    };

    return check(this.root).balanced;
  }

  // ---------------------------
  // REBALANCE
  // ---------------------------
  rebalance() {
    const values = this.inOrder();
    this.root = this.buildTree(values);
  }

  // ---------------------------
  // PRETTY PRINT
  // ---------------------------
  prettyPrint(node = this.root, prefix = "", isLeft = true) {
    if (node.right)
      this.prettyPrint(node.right, prefix + (isLeft ? "│   " : "    "), false);

    console.log(prefix + (isLeft ? "└── " : "┌── ") + node.data);

    if (node.left)
      this.prettyPrint(node.left, prefix + (isLeft ? "    " : "│   "), true);
  }
}

// ---------------------------
// DRIVER SCRIPT (ejemplo)
// ---------------------------
const tree = new Tree([1, 7, 4, 23, 8, 9, 4, 3, 5, 7, 9]);

console.log("\nInitial tree:");
tree.prettyPrint();

console.log("\nInorder:", tree.inOrder().join(" "));
console.log("Preorder:", tree.preOrder().join(" "));
console.log("Postorder:", tree.postOrder().join(" "));
console.log("Level order:", tree.levelOrder().join(" "));

console.log("\n¿Is it balanced?", tree.isBalanced());

tree.insert(100);
tree.insert(120);
tree.insert(150);

console.log("\After balancing:");
tree.prettyPrint();
console.log("Is it balanced?", tree.isBalanced());

tree.rebalance();

console.log("\nRebalanced:");
tree.prettyPrint();
console.log("¿Is it balanced?", tree.isBalanced());
