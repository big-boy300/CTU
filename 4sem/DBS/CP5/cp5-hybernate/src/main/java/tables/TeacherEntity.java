package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "teacher"/*, schema = "public", catalog = "danilrom"*/)
public class TeacherEntity extends PersonEntity {
    @OneToMany(mappedBy = "teacherByTeacherid")
    private Collection<StudygroupEntity> studygroupsByLangschoolcardnumber;
    @OneToOne(mappedBy = "teacherByTeacherid")
    private TeacheraccountownershipEntity teacheraccountownershipByLangschoolcardnumber;

    public Collection<StudygroupEntity> getStudygroupsByLangschoolcardnumber() {
        return studygroupsByLangschoolcardnumber;
    }

    public void setStudygroupsByLangschoolcardnumber(Collection<StudygroupEntity> studygroupsByLangschoolcardnumber) {
        this.studygroupsByLangschoolcardnumber = studygroupsByLangschoolcardnumber;
    }

    public TeacheraccountownershipEntity getTeacheraccountownershipByLangschoolcardnumber() {
        return teacheraccountownershipByLangschoolcardnumber;
    }

    public void setTeacheraccountownershipByLangschoolcardnumber(TeacheraccountownershipEntity teacheraccountownershipByLangschoolcardnumber) {
        this.teacheraccountownershipByLangschoolcardnumber = teacheraccountownershipByLangschoolcardnumber;
    }

}
