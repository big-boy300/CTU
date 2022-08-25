package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "student")
public class StudentEntity extends PersonEntity {
    @Basic
    @Column(name = "startinglanguagelevel")
    private String startinglanguagelevel;
    @OneToOne(mappedBy = "studentByStudentid")
    private InvitationEntity invitationByLangschoolcardnumber;
    @OneToMany(mappedBy = "studentByFriendid")
    private Collection<InvitationEntity> invitationsByLangschoolcardnumber;
    @OneToMany(mappedBy = "studentByStudentid")
    private Collection<LessonEntity> lessonsByLangschoolcardnumber;
    @OneToMany(mappedBy = "studentByStudentid")
    private Collection<PaymentEntity> paymentsByLangschoolcardnumber;
    @OneToOne(mappedBy = "studentByStudentid")
    private StudentaccountownershipEntity studentaccountownershipByLangschoolcardnumber;


    public String getStartinglanguagelevel() {
        return startinglanguagelevel;
    }

    public void setStartinglanguagelevel(String startinglanguagelevel) {
        this.startinglanguagelevel = startinglanguagelevel;
    }

    public InvitationEntity getInvitationByLangschoolcardnumber() {
        return invitationByLangschoolcardnumber;
    }

    public void setInvitationByLangschoolcardnumber(InvitationEntity invitationByLangschoolcardnumber) {
        this.invitationByLangschoolcardnumber = invitationByLangschoolcardnumber;
    }

    public Collection<InvitationEntity> getInvitationsByLangschoolcardnumber() {
        return invitationsByLangschoolcardnumber;
    }

    public void setInvitationsByLangschoolcardnumber(Collection<InvitationEntity> invitationsByLangschoolcardnumber) {
        this.invitationsByLangschoolcardnumber = invitationsByLangschoolcardnumber;
    }

    public Collection<LessonEntity> getLessonsByLangschoolcardnumber() {
        return lessonsByLangschoolcardnumber;
    }

    public void setLessonsByLangschoolcardnumber(Collection<LessonEntity> lessonsByLangschoolcardnumber) {
        this.lessonsByLangschoolcardnumber = lessonsByLangschoolcardnumber;
    }

    public Collection<PaymentEntity> getPaymentsByLangschoolcardnumber() {
        return paymentsByLangschoolcardnumber;
    }

    public void setPaymentsByLangschoolcardnumber(Collection<PaymentEntity> paymentsByLangschoolcardnumber) {
        this.paymentsByLangschoolcardnumber = paymentsByLangschoolcardnumber;
    }

    public StudentaccountownershipEntity getStudentaccountownershipByLangschoolcardnumber() {
        return studentaccountownershipByLangschoolcardnumber;
    }

    public void setStudentaccountownershipByLangschoolcardnumber(StudentaccountownershipEntity studentaccountownershipByLangschoolcardnumber) {
        this.studentaccountownershipByLangschoolcardnumber = studentaccountownershipByLangschoolcardnumber;
    }

    @Override
    public String toString() {
        return "StudentEntity{" +
                "startinglanguagelevel='" + startinglanguagelevel + '\'' +
                '}';
    }
}
