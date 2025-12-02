import Node from "./Node.js"

class LinkedList {
  #head

  constructor() {
    this.node = null
    this.#head = this.node
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

  prepend(value) {
    const temp = this.node
    this.node = new Node(value)
    this.node.nextNode = temp
    this.#head = this.node
  }

  size() {
    if (!this.node) {
      return 0
    }

    let num = 1
    if (this.#head.nextNode === null) {
      this.#head = this.node
      return 1
    }

    this.#head = this.#head.nextNode
    return num + this.size()
  }

  head() {
    return this.#head
  }

  tail() {
    if (this.#head.nextNode === null) {
      const tail = this.#head
      this.#head = this.node
      return tail
    }

    this.#head = this.#head.nextNode
    return this.tail()
  }

  at(index) {
    if ((index + 1) > this.size() || index < 0) {
      throw new Error('Index out of bounds')
    }

    for (let i = 0; i < index; i++) {
      this.#head = this.#head.nextNode
    }

    const node = this.#head
    this.#head = this.node
    return node
  }

  pop() {
    if (this.#head.nextNode.nextNode === null) {
      this.#head.nextNode = null
      this.#head = this.node
      return
    }

    this.#head = this.#head.nextNode
    this.pop()
  }

  contains(value) {
    if (this.#head.value !== value && this.#head.nextNode === null) {
      this.#head = this.node
      return false
    }

    if (this.#head.value === value) {
      this.#head = this.node
      return true
    }

    this.#head = this.#head.nextNode
    return true && this.contains(value)
  }

  find(value) {
    let index = 0
    while (this.#head) {
      if (this.#head.value === value) {
        this.#head = this.node
        return index
      }
      this.#head = this.#head.nextNode
      index += 1
    }

    this.#head = this.node
    return null
  }

  toString() {
    let current = this.#head
    let output = ''
    while (true) {
      if (current.nextNode === null) {
        output += `( ${current.value} ) -> null`
        break
      }
      output += `( ${current.value} ) -> `
      current = current.nextNode
    }

    return output
  }
}

export default LinkedList