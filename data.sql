CREATE TABLE IF NOT EXISTS todo_lists (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL UNIQUE COLLATE NOCASE);

CREATE TABLE IF NOT EXISTS todo_items (
    id INTEGER PRIMARY KEY,
    list_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    completed INTEGER NOT NULL DEFAULT 0,
    FOREIGN KEY(list_id) REFERENCES todo_lists(id));