import Node from "./Node.js"

class LinkedList {
  #head
  constructor() {
    this.node = null
    this.#head = this.node
  }
}

  append(value) {
    if (!this.node) {
      this.node = new Node(value)
    } else if (!this.#head.nextNode) {
      this.#head.nextNode = new Node(value)
    } else {
      this.#head = this.#head.nextNode
      this.append(value)
    }

    this.#head = this.node
  }