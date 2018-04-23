template <typename V>
class ascending {
public:
    bool operator()(V x, V y) const {
        if(x<=y) return true;
        return false;
    }
};

template <typename V>
class descending {
public:
    bool operator()(V x, V y) const {
        if(x>=y) return true;
        return false;
    }
};