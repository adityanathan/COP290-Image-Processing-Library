class Vector
{

    private:
        int max = 10;
        float* vec;
        int n = 0;

    public:
        //Constructor
        Vector();

        //Setters
        void push(float a);

        //Getters
        float get(int i);


};