void kernel simple_add(global int *data, global int *a) {
    int v = get_global_id(0);
    a[v] = v + data[v];
}
