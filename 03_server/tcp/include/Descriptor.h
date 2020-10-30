namespace TCP {


class Descriptor {
public:
    Descriptor(int fd = -1);
    ~Descriptor();
    Descriptor(const Descriptor& other) = delete;
    Descriptor(Descriptor&& other);

    int getValue() const;
    void setValue(int fd);
    Descriptor& operator=(int fd);

    void close();
private:
    int fd_ = -1;
};

} // TCP
