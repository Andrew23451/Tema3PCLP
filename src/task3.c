#include "task3.h"
#include "math.h"

typedef struct {
    unsigned char *block;
    size_t size;
} Block;

typedef struct {
    Block blocks[4];
} StudentBlocks;

StudentBlocks split_students_into_blocks(const student *studenti, size_t num_students) {
    StudentBlocks sbv;
    size_t total_size = sizeof(student) * num_students;
    size_t padded_block_size = (size_t)(ceil((double)total_size / 4));

    unsigned char *data = (unsigned char *)studenti;

    for (int i = 0; i < 4; i++) {
        sbv.blocks[i].size = padded_block_size;
        sbv.blocks[i].block = (unsigned char *)malloc(padded_block_size);
        for (size_t j = 0; j < padded_block_size; j++) {
            size_t index = i * padded_block_size + j;
            sbv.blocks[i].block[j] = (index < total_size) ? data[index] : 0x00;
        }
    }

    return sbv;
}


void P_BOX(unsigned char *block, size_t block_size) {
    unsigned char temp[block_size];
    memcpy(temp, block, block_size);
    for (size_t i = 0; i < block_size; i++) {
        block[i] = temp[(i * (block_size - 1) + 2) % block_size];
    }
}

void XOR_blocks(const unsigned char *block, size_t block_size, const char *message,
               size_t message_len, unsigned char *result) {
    for (size_t i = 0; i < block_size; ++i) {
        unsigned char message_byte = message[i % message_len];
        result[i] = block[i] ^ message_byte;
    }
}


void cripteaza_studenti(secretariat *secretariat, void *key, size_t key_len,
                        void *iv, size_t iv_len, char *cale_output) {
    FILE *output_file = fopen(cale_output, "wb");
    if (!output_file) {
        perror("Error opening output file");
        return;
    }

    StudentBlocks sb = split_students_into_blocks(secretariat->studenti, secretariat->nr_studenti);
    unsigned char *encrypted_block0 = (unsigned char *)malloc(sb.blocks[0].size);
    if (!encrypted_block0) {
        perror("Error allocating memory for encryption");
        fclose(output_file);
        return;
    }

    XOR_blocks(sb.blocks[0].block, sb.blocks[0].size, (char *)iv, iv_len, encrypted_block0);

    unsigned char *doubly_encrypted_block0 = (unsigned char *)malloc(sb.blocks[0].size);
    if (!doubly_encrypted_block0) {
        perror("Error allocating memory for double encryption");
        free(encrypted_block0);
        fclose(output_file);
        return;
    }
    XOR_blocks(encrypted_block0, sb.blocks[0].size, (char *)key, key_len, doubly_encrypted_block0);

    P_BOX(doubly_encrypted_block0, sb.blocks[0].size);

    unsigned char *encrypted_blocks[4];
    encrypted_blocks[0] = doubly_encrypted_block0;

    for (int j = 1; j < 4; j++) {
        encrypted_blocks[j] = (unsigned char *)malloc(sb.blocks[j].size);
        if (!encrypted_blocks[j]) {
            perror("Error allocating memory for block encryption");
            for (int k = 0; k < j; k++) {
                free(encrypted_blocks[k]);
            }
            fclose(output_file);
            return;
        }
        XOR_blocks(sb.blocks[j].block, sb.blocks[j].size, (char *)encrypted_blocks[j - 1],
                    sb.blocks[j - 1].size, encrypted_blocks[j]);
        XOR_blocks(encrypted_blocks[j], sb.blocks[j].size, (char *)key, key_len, encrypted_blocks[j]);
        P_BOX(encrypted_blocks[j], sb.blocks[j].size);
    }

    for (int j = 0; j < 4; j++) {
        fwrite(encrypted_blocks[j], 1, sb.blocks[j].size, output_file);
        free(encrypted_blocks[j]);
        free(sb.blocks[j].block);
    }
    free(encrypted_block0);

    fclose(output_file);
}
