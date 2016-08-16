#ifndef MBASE_H
#define MBASE_H


class mBase
{
    public:
		mBase();
        virtual bool Init();
        virtual void Update();
        virtual void Quit();
    protected:
    private:
};

#endif // MBASE_H
