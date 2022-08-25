package dao;

import java.util.HashMap;

public interface DAOLayer {

    void findData(HashMap<String, String> pks);

    void addData(HashMap<String, String> data);

    void removeData(HashMap<String, String> pks);

    void updateData(HashMap<String, String> pks, HashMap<String, String> newData);
}
