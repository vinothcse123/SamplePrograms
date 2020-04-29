    class CSingletonClass
    {
    private:
        CSingletonClass();
        CSingletonClass(const CSingletonClass &) = delete;
        CSingletonClass &operator=(const CSingletonClass &) const = delete;

    public:
        static CSingletonClass &getInstance()
        {
            static CSingletonClass singletonClass;
            return singletonClass;
        }
    };
