let graph = [
  [0, 1, 0, 1, 1],
  [0, 0, 0, 1, 0],
  [0, 1, 0, 0, 1],
  [1, 0, 0, 0, 0],
  [0, 0, 1, 0, 0],
];
let checked = [false, false, false, false, false];

let stack = [];

let dfs = (graph, vertex) => {
  stack = [vertex];
  while (stack.length) {
    let v = stack.pop();
    if (!checked[v]) {
      visit(v);
      checked[v] = true;

      for (let i = 0; i < graph.length; i++) {
        if (graph[v][i] && !checked[i]) {
          stack.push(i);
        }
      }
    }
  }
};

let visit = (vertex) => {
  console.log(vertex);
};

dfs(graph, 0);
