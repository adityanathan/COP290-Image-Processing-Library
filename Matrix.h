class Matrix
{
    private:
        float** mat;
        int max_row;
        int row=0;
        int col=0;

    public:
        Matrix(int max_row);
        Matrix(float** obj);
        // Matrix(Matrix &obj);
        void create_matrix(string path);
        float get(int i, int j);
        void set(float a, int i, int j);
        void delete_matrix();
        int get_max_rows();
        Matrix reflect_matrix();
};