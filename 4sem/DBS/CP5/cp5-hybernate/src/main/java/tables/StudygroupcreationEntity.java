package tables;

import javax.persistence.*;

@Entity
@Table(name = "studygroupcreation", schema = "public", catalog = "danilrom")
@IdClass(StudygroupcreationEntityPK.class)
public class StudygroupcreationEntity {
    @Id
    @Column(name = "employeeid")
    private String employeeid;
    @Id
    @Column(name = "teacherid")
    private String teacherid;
    @Id
    @Column(name = "level")
    private String level;
    @Id
    @Column(name = "language")
    private String language;
    @ManyToOne
    @JoinColumn(name = "employeeid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByEmployeeid;
    @ManyToOne
    @JoinColumn(name = "employeeid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private StaffEntity staffByEmployeeid;
    @ManyToOne
    @JoinColumns({@JoinColumn(name = "teacherid", referencedColumnName = "teacherid", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "level", referencedColumnName = "level", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "language", referencedColumnName = "language", nullable = false, insertable = false, updatable = false)})
    private StudygroupEntity studygroupByFkStudygroupcreationTeacherid;
    @ManyToOne
    @JoinColumns({@JoinColumn(name = "teacherid", referencedColumnName = "teacherid", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "level", referencedColumnName = "level", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "language", referencedColumnName = "language", nullable = false, insertable = false, updatable = false)})
    private StudygroupEntity studygroupByStudygroupcreationFkTeacherLevelLang;

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

        StudygroupcreationEntity that = (StudygroupcreationEntity) o;

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
