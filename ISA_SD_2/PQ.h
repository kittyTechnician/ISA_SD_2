#pragma once

class PQ {
public:
    virtual ~PQ() = default;

    virtual void insert(int e, int p) = 0;
    virtual int extract_max() = 0;
    virtual int find_max() const = 0;
    virtual void modify_key(int e, int p) = 0;
    virtual int return_size() const = 0;
};