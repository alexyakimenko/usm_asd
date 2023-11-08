let adjacency_list = [[1, 3, 2], [0, 3], [0, 3], [0, 1, 2, 4], [3]];

let checked = [false, false, false, false, false];

let dfs = (graph, vertex) => {
  let queue = [vertex];
  while (queue.length > 0) {
    let v = queue.shift();
    if (checked[v]) continue;
    visit(v);
    checked[v] = true;
    for (let n of graph[v]) {
      if (checked[n]) continue;
      queue.push(n);
    }
  }
};

let visit = (el) => {
  console.log(el);
};

dfs(adjacency_list, 0);
