package tables;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.io.Serializable;

public class StudygroupcreationEntityPK implements Serializable {
    @Column(name = "employeeid")
    @Id
    private String employeeid;
    @Column(name = "teacherid")
    @Id
    private String teacherid;
    @Column(name = "level")
    @Id
    private String level;
    @Column(name = "language")
    @Id
    private String language;

    public String getEmployeeid() {
        return employeeid;
    }

    public void setEmployeeid(String employeeid) {
        this.employeeid = employeeid;
    }

    public String getTeacherid() {
        return teacherid;
    }

    public void setTeacherid(String teacherid) {
        this.teacherid = teacherid;
    }

    public String getLevel() {
        return level;
    }

    public void setLevel(String level) {
        this.level = level;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        StudygroupcreationEntityPK that = (StudygroupcreationEntityPK) o;

        if (employeeid != null ? !employeeid.equals(that.employeeid) : that.employeeid != null) return false;
        if (teacherid != null ? !teacherid.equals(that.teacherid) : that.teacherid != null) return false;
        if (level != null ? !level.equals(that.level) : that.level != null) return false;
        if (language != null ? !language.equals(that.language) : that.language != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = employeeid != null ? employeeid.hashCode() : 0;
        result = 31 * result + (teacherid != null ? teacherid.hashCode() : 0);
        result = 31 * result + (level != null ? level.hashCode() : 0);
        result = 31 * result + (language != null ? language.hashCode() : 0);
        return result;
    }
}
