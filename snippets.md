### .vimrc

```
inoremap jk <Esc>

set incsearch
set hlsearch

nnoremap <silent><Cr> :noh<Cr>
```

### .inputrc

```
set editing-mode vi

set keymap vi-insert

"jk": "\e"
```

### c++ snippets

```c++
ios_base::sync_with_stdio(false);
cin.tie(NULL);

// a binary to unary tool for std::find_if
template <typename T>
struct ptrEqual {
	T* _other;
	ptrEqual(T* other) : _other(other) {}
	bool operator()(T*& current) const {
		return (*current == *_other);
	}
};

// predicate for unordered_set
template <typename T>
struct binaryPtrEqual {
	bool operator()(T* const& left, T* const& right) const {
		return (*left == *right);
	}
};
```

### outputs.sh

```bash
#!/bin/bash -xe
inputs="testdata_students/*.in"
regex="([a-z]+[0-9]+).in"
for f in $inputs; do
	if [[ $f =~ $regex ]]
	then
		test_case="${BASH_REMATCH[1]}"
	fi
	out_name="testdata_students/${test_case}.actual"
	./a.out < $f > $out_name
done
```

### diffs.sh

```bash
#!/bin/bash -xe
act_outputs="testdata_students/*.actual"
regex="([a-z]+[0-9]+).actual"
for f in $act_outputs; do
	if [[ $f =~ $regex ]]
	then
		test_case="${BASH_REMATCH[1]}"
	fi
	out_name="testdata_students/$test_case.out"
	diff $f $out_name
done
```
